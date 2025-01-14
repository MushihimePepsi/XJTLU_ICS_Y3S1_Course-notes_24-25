from ryu.base import app_manager
from ryu.controller import ofp_event
from ryu.controller.handler import CONFIG_DISPATCHER, MAIN_DISPATCHER
from ryu.controller.handler import set_ev_cls
from ryu.lib.packet import ipv4, tcp
from ryu.ofproto import ofproto_v1_3
from ryu.lib.packet import packet
from ryu.lib.packet import ethernet
from ryu.lib.packet import ether_types

SERVER1 = {'ip': '10.0.1.2', 'mac': '00:00:00:00:00:01'}
SERVER2 = {'ip': '10.0.1.3', 'mac': '00:00:00:00:00:02'}
CLIENT = {'ip': '10.0.1.5', 'mac': '00:00:00:00:00:03'}


class RedirectSwitch(app_manager.RyuApp):
    # use OPenFlow 1.3
    OFP_VERSIONS = [ofproto_v1_3.OFP_VERSION]

    def __init__(self, *args, **kwargs):
        super(RedirectSwitch, self).__init__(*args, **kwargs)
        self.mac_to_port = {}

    @set_ev_cls(ofp_event.EventOFPSwitchFeatures, CONFIG_DISPATCHER)
    def switch_features_handler(self, ev):
        datapath = ev.msg.datapath
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser

        match = parser.OFPMatch()
        actions = [parser.OFPActionOutput(ofproto.OFPP_CONTROLLER, ofproto.OFPCML_NO_BUFFER)]
        self.add_flow(datapath, 0, match, actions)

    def add_flow(self, datapath, priority, match, actions, buffer_id=None, timeout=False):
        # print(f'data path={datapath}, priority={priority}, match={match}, action={actions}, buffer_id={buffer_id}')
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser

        inst = [parser.OFPInstructionActions(ofproto.OFPIT_APPLY_ACTIONS, actions)]

        # 5 sec idle timeout
        if buffer_id:
            mod = parser.OFPFlowMod(datapath=datapath, buffer_id=buffer_id, priority=priority, match=match,
                                    instructions=inst, idle_timeout=5 if timeout else 0)
        else:
            mod = parser.OFPFlowMod(datapath=datapath, priority=priority, match=match, instructions=inst,
                                    idle_timeout=5 if timeout else 0)
        datapath.send_msg(mod)

    @set_ev_cls(ofp_event.EventOFPPacketIn, MAIN_DISPATCHER)
    def _packet_in_handler(self, ev):
        if ev.msg.msg_len < ev.msg.total_len:
            self.logger.debug("packet truncated: only %s of %s bytes", ev.msg.msg_len, ev.msg.total_len)
        msg = ev.msg

        datapath = msg.datapath
        dpid = datapath.id
        self.mac_to_port.setdefault(dpid, {})

        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser
        in_port = msg.match['in_port']

        pkt = packet.Packet(msg.data)
        eth = pkt.get_protocols(ethernet.ethernet)[0]
        if eth.ethertype == ether_types.ETH_TYPE_LLDP:
            # ignore lldp packet
            return
        dst = eth.dst
        src = eth.src

        self.logger.info(f'packet in: dpid={dpid}  src={src}  dst={dst}  in_port={in_port}')

        # self-learn
        self.mac_to_port[dpid][src] = in_port

        if dst in self.mac_to_port[dpid]:
            out_port = self.mac_to_port[dpid][dst]
        else:
            out_port = ofproto.OFPP_FLOOD

        actions = [parser.OFPActionOutput(out_port)]

        if out_port != ofproto.OFPP_FLOOD:
            # redirect client -> server1 to server 2
            ipv4_pkt = pkt.get_protocol(ipv4.ipv4)
            tcp_pkt = pkt.get_protocol(tcp.tcp)
            if ipv4_pkt and tcp_pkt:
                self.logger.info(f'IPV4 pkt={ipv4_pkt}\nTCP pkt={tcp_pkt}')
                ipv4_src = ipv4_pkt.src
                ipv4_dst = ipv4_pkt.dst

                # redirect client->server1's tcp conn to server2
                # change the dst to server2
                if src == CLIENT['mac'] and dst == SERVER1['mac']:
                    print('client to server1')

                    if SERVER2['mac'] in self.mac_to_port[dpid]:
                        out_port = self.mac_to_port[dpid][SERVER2['mac']]
                    else:
                        out_port = ofproto.OFPP_FLOOD

                    match = parser.OFPMatch(eth_type=ether_types.ETH_TYPE_IP, ipv4_src=ipv4_src, ipv4_dst=ipv4_dst)
                    actions = [parser.OFPActionSetField(eth_dst=SERVER2['mac']),
                               parser.OFPActionSetField(ipv4_dst=SERVER2['ip']),
                               parser.OFPActionOutput(out_port)]

                # need to modify the return tcp packet
                # change the src from server2 to server1
                elif src == SERVER2['mac'] and dst == CLIENT['mac']:
                    print('server to client')

                    if CLIENT['mac'] in self.mac_to_port[dpid]:
                        out_port = self.mac_to_port[dpid][CLIENT['mac']]
                    else:
                        out_port = ofproto.OFPP_FLOOD

                    match = parser.OFPMatch(eth_type=ether_types.ETH_TYPE_IP, ipv4_src=ipv4_src, ipv4_dst=ipv4_dst)
                    actions = [parser.OFPActionSetField(eth_src=SERVER1['mac']),
                               parser.OFPActionSetField(ipv4_src=SERVER1['ip']),
                               parser.OFPActionOutput(out_port)]

                else:
                    match = parser.OFPMatch(in_port=in_port, eth_dst=dst, eth_src=src)
            else:
                match = parser.OFPMatch(in_port=in_port, eth_dst=dst, eth_src=src)

            if msg.buffer_id != ofproto.OFP_NO_BUFFER:
                self.add_flow(datapath, 1, match, actions, msg.buffer_id, True)
                return
            else:
                self.add_flow(datapath, 1, match, actions, None, True)

        data = None
        if msg.buffer_id == ofproto.OFP_NO_BUFFER:
            data = msg.data

        out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id, in_port=in_port, actions=actions,
                                  data=data)
        self.logger.info(
            f'packet out: dpid={dpid}  action={actions}  buffer_id={msg.buffer_id} in_port={in_port} out_port={out_port}')

        datapath.send_msg(out)
