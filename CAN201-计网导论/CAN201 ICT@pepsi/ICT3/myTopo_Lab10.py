#/usr/bin/python
from mininet.net import Mininet
from mininet.cli import CLI
from mininet.node import Host
from mininet.node import OVSKernelSwitch
from mininet.log import setLogLevel, info
from mininet.node import RemoteController
from mininet.term import makeTerm


def myTopo():
    # Create an empty network with specified IP base
    net = Mininet(topo=None, autoSetMacs=True, build=False, ipBase='10.0.1.0/24')
    
    # add controller
    c1 = net.addController('c1', RemoteController)
    
    # Add hosts
    h1 = net.addHost('h1', cls=Host, defaultRoute=None)
    h2 = net.addHost('h2', cls=Host, defaultRoute=None)
    h3 = net.addHost('h3', cls=Host, defaultRoute=None)
    
    # Add switch
    s1 = net.addSwitch('s1', cls=OVSKernelSwitch, failMode='secure')
    
    # Add links between hosts and switches
    net.addLink(h1, s1, intfName1='h1-eth0')
    net.addLink(h2, s1, intfName1='h2-eth0')
    net.addLink(h3, s1, intfName1='h3-eth0')
    
    # Build the network
    net.build()
    
    # set mac to interface
    h1.setMAC(intf="h1-eth0", mac="00:00:00:00:00:11")
    h2.setMAC(intf="h2-eth0", mac="00:00:00:00:00:21")
    h3.setMAC(intf="h3-eth0", mac="00:00:00:00:00:31")
    
    # Configure IP addresses
    h1.setIP(intf="h1-eth0", ip='10.0.1.2/24')
    h2.setIP(intf="h2-eth0", ip='10.0.1.3/24')
    h3.setIP(intf="h3-eth0", ip='10.0.1.15/24')
    
    # Start the network
    net.start()
    
    # start xterms
    net.terms += makeTerm(c1)
    net.terms += makeTerm(s1)
    net.terms += makeTerm(h1)
    net.terms += makeTerm(h2)
    net.terms += makeTerm(h3)
    
    # Drop into CLI mode
    CLI(net)
    # Stop the network
    net.stop()


if __name__ == '__main__':
    setLogLevel('info')
    myTopo()
