from mininet.term import makeTerm
from mininet.net import Mininet
from mininet.cli import CLI
from mininet.node import Host, RemoteController
from mininet.node import OVSKernelSwitch
from mininet.log import setLogLevel, info


def main():
    net = Mininet(topo=None, autoSetMacs=True, build=False, ipBase='10.0.1.0/24')

    # server1 = net.addHost('server1', cls=Host, defaultRoute=None)
    # server2 = net.addHost('server2', cls=Host, defaultRoute=None)
    # client = net.addHost('client', cls=Host, defaultRoute=None)

    server1 = net.addHost('server1', ip='10.0.1.2/24', mac='00:00:00:00:00:01', cls=Host, defaultRoute=None)
    server2 = net.addHost('server2', ip='10.0.1.3/24', mac='00:00:00:00:00:02', cls=Host, defaultRoute=None)
    client = net.addHost('client', ip='10.0.1.5/24', mac='00:00:00:00:00:03', cls=Host, defaultRoute=None)

    sdn_switch = net.addSwitch('s1', cls=OVSKernelSwitch, failmode='secure')
    controller = net.addController('c0', controller=RemoteController)

    net.addLink(client, sdn_switch)
    net.addLink(server1, sdn_switch)
    net.addLink(server2, sdn_switch)

    net.build()
    controller.start()
    sdn_switch.start([controller])

    # terminals
    net.terms += makeTerm(server1)
    net.terms += makeTerm(server2)
    net.terms += makeTerm(client)
    net.terms += makeTerm(controller)
    net.terms += makeTerm(sdn_switch)

    CLI(net)
    net.stop()


if __name__ == '__main__':
    setLogLevel('info')
    main()
