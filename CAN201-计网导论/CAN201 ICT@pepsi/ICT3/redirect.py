from ryu.base import app_manager  # ryu app 的基础
from ryu.controller import ofp_event  # 定义Openflow的事件，如PacketIn, SwitchFeatures
from ryu.controller.handler import CONFIG_DISPATCHER, MAIN_DISPATCHER  # 异步处理事件驱动的OpenFlow的messages
from ryu.controller.handler import set_ev_cls
from ryu.ofproto import ofproto_v1_3  # Openflow1.3协议
from ryu.lib.packet import packet, tcp, ipv4, ether_types, ethernet  # 解析与创包的工具
from ryu.lib.packet.ether_types import ETH_TYPE_IP


class RedirectSwitch(app_manager.RyuApp):
    # use OpenFlow 1.3
    OFP_VERSIONS = [ofproto_v1_3.OFP_VERSION]
    
    def __init__(self, *args, **kwargs):
        super(RedirectSwitch, self).__init__(*args, **kwargs)
        self.mac_to_port = {}
    
    @set_ev_cls(ofp_event.EventOFPSwitchFeatures, CONFIG_DISPATCHER)
    def switch_features_handler(self, ev):
        """根据CONFIG_DISPATCHER的状态被触发（当交换机连接至controller时）
        添加table-miss flow entry确保不符合的包被发送到controller
        应该是只会在交换机第一次连接时触发
        :param ev:
        :return: nothing
        """
        # print('!!!switch_features_handler!!!')
        
        datapath = ev.msg.datapath
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser
        
        match = parser.OFPMatch()
        actions = [parser.OFPActionOutput(ofproto.OFPP_CONTROLLER, ofproto.OFPCML_NO_BUFFER)]
        self.add_flow(datapath, 0, match, actions)
    
    def add_flow(self, datapath, priority, match, actions, buffer_id=None, timeout=False):
        """添加flow entry到交换机flow table
        如果两个连接是第一次连接，即连接不在流表中时，会运行。
        :param datapath:
        :param priority:
        :param match:
        :param actions:
        :param buffer_id:
        :param timeout:
        :return:
        """
        # print(f'!!!add_flow!!!\n')
        
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser
        
        inst = [parser.OFPInstructionActions(ofproto.OFPIT_APPLY_ACTIONS, actions)]
        
        print('\n in_port=', match.get('in_port'),
              '\n eth_dst=', match.get('eth_dst'),
              '\n eth_src=', match.get('eth_src'))
        
        if buffer_id:
            mod = parser.OFPFlowMod(datapath=datapath, buffer_id=buffer_id,
                                    priority=priority, match=match,
                                    instructions=inst, idle_timeout=5 if timeout else 0)
        else:
            mod = parser.OFPFlowMod(datapath=datapath, priority=priority,
                                    match=match, instructions=inst, idle_timeout=5 if timeout else 0)
        # print('MOD=',mod)
        datapath.send_msg(mod)  # 向交换机安装或修改流表条目。交换机根据 mod 的内容将流表规则添加到硬件或软件表中。
    
    @set_ev_cls(ofp_event.EventOFPPacketIn, MAIN_DISPATCHER)
    def _packet_in_handler(self, ev):
        """装饰器 @set_ev_cls 限制了方法仅在收到EventOFPPacketIn且状态MAIN_DISPATCHER下处理事件
        在交换机工作正常时，控制器接收未匹配流表的包，并决定如何处理这些数据包
        :param ev:
        :return:
        """
        # print('!!!_packet_in_handler!!!\n', ev)
        
        # If you hit this you might want to increase
        # the "miss_send_length" of your switch
        if ev.msg.msg_len < ev.msg.total_len:
            self.logger.debug("packet truncated: only %s of %s bytes",
                              ev.msg.msg_len, ev.msg.total_len)
        msg = ev.msg
        
        datapath = msg.datapath
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser
        dpid = datapath.id
        in_port = msg.match['in_port']
        
        pkt = packet.Packet(msg.data)
        eth = pkt.get_protocols(ethernet.ethernet)[0]
        dst = eth.dst  # mac地址
        src = eth.src
        print('dst,src:', dst, src)
        
        ipv4_pkt = pkt.get_protocol(ipv4.ipv4)
        tcp_pkt = pkt.get_protocol(tcp.tcp)
        print("ipv4_pkt, tcp_pkt\n", ipv4_pkt, tcp_pkt)
        
        client_mac = '00:00:00:00:00:03'
        client_ip = '10.0.1.5'
        server1_mac = '00:00:00:00:00:01'
        server1_ip = '10.0.1.2'
        server2_mac = '00:00:00:00:00:02'
        server2_ip = '10.0.1.3'
        
        # 如果是系统LLDP包，忽略 ignore lldp packet
        if eth.ethertype == ether_types.ETH_TYPE_LLDP:
            return
        
        # 如果是ipv4的tcp包，进行处理
        elif ipv4_pkt and tcp_pkt:
            self.logger.info("IPv4 pkt: %s\n TCP pkt: %s", ipv4_pkt, tcp_pkt)
            ipv4_src = ipv4_pkt.src  # ip地址
            ipv4_dst = ipv4_pkt.dst
            # print('ipv4_src, ipv4_dst', ipv4_src, ipv4_dst)
            
            # redirect traffic
            if dst == server1_mac and src == client_mac:
                print('received client to server1, redirect to server2')
                if server2_mac in self.mac_to_port[dpid]:
                    out_port = self.mac_to_port[dpid][server2_mac]
                else:
                    out_port = ofproto.OFPP_FLOOD
                match = parser.OFPMatch(eth_type=ether_types.ETH_TYPE_IP, ipv4_src=ipv4_src, ipv4_dst=ipv4_dst)
                actions = [
                    parser.OFPActionSetField(eth_dst=server2_mac),
                    parser.OFPActionSetField(ipv4_dst=server2_ip),
                    parser.OFPActionOutput(out_port)
                ]
            
            # 回程包
            elif dst == client_mac and src == server2_mac:
                print('received server2 to client, direct to client')
                if client_mac in self.mac_to_port[dpid]:
                    out_port = self.mac_to_port[dpid][client_mac]
                else:
                    out_port = ofproto.OFPP_FLOOD
                match = parser.OFPMatch(eth_type=ether_types.ETH_TYPE_IP, ipv4_src=ipv4_src, ipv4_dst=ipv4_dst)
                actions = [
                    parser.OFPActionSetField(eth_src=server1_mac),
                    parser.OFPActionSetField(ipv4_src=server1_ip),
                    parser.OFPActionOutput(out_port)
                ]
            
            # tcp但不是目标的包
            else:
                if dst in self.mac_to_port[dpid]:
                    out_port = self.mac_to_port[dpid][dst]
                else:
                    out_port = ofproto.OFPP_FLOOD
                
                actions = [parser.OFPActionOutput(out_port)]
                
                match = parser.OFPMatch(in_port=in_port, eth_dst=dst, eth_src=src)
            
            # 对以上三种情况add_flow
            if msg.buffer_id != ofproto.OFP_NO_BUFFER:
                self.add_flow(datapath, 1, match, actions, msg.buffer_id)
                return
            else:
                self.add_flow(datapath, 1, match, actions)
        
        # 其他情况
        else:
            self.mac_to_port.setdefault(dpid, {})
            self.logger.info("packet in %s %s %s %s", dpid, src, dst, in_port)
            self.mac_to_port[dpid][src] = in_port
            
            if dst in self.mac_to_port[dpid]:
                out_port = self.mac_to_port[dpid][dst]
            else:
                out_port = ofproto.OFPP_FLOOD
            
            actions = [parser.OFPActionOutput(out_port)]
            
            if out_port != ofproto.OFPP_FLOOD:
                match = parser.OFPMatch(in_port=in_port, eth_dst=dst, eth_src=src)
                if msg.buffer_id != ofproto.OFP_NO_BUFFER:
                    self.add_flow(datapath, 1, match, actions, msg.buffer_id, True)
                    return
                else:
                    self.add_flow(datapath, 1, match, actions, None, True)
        
        data = None
        if msg.buffer_id == ofproto.OFP_NO_BUFFER:
            data = msg.data
        out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id,
                                  in_port=in_port, actions=actions, data=data)
        datapath.send_msg(out)  # 将Packet_Out消息从控制器发送到交换机，指示交换机如何处理该数据包。