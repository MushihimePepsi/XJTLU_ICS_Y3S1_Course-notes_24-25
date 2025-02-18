#!/usr/bin/python

from mininet.net import Mininet
from mininet.cli import CLI
from mininet.node import Host
from mininet.node import OVSKernelSwitch
from mininet.log import setLogLevel, info


def myTopo():
    # Create an empty network with specified IP base
    net = Mininet(topo=None, autoSetMacs=True, build=False, ipBase='192.168.45.0/24')
    
    # Add hosts
    h1 = net.addHost('h1', cls=Host, defaultRoute=None)
    h2 = net.addHost('h2', cls=Host, defaultRoute=None)
    h3 = net.addHost('h3', cls=Host, defaultRoute=None)
    
    # Add switches
    s1 = net.addSwitch('s1', cls=OVSKernelSwitch, failMode='standalone')
    s2 = net.addSwitch('s2', cls=OVSKernelSwitch, failMode='standalone')
    
    # Add links between hosts and switches
    net.addLink(h1, s1, intfName1='h1-eth0')
    net.addLink(h3, s2, intfName1='h3-eth0')
    net.addLink(h2, s1, intfName1='h2-eth0')
    net.addLink(h2, s2, intfName1='h2-eth1')
    
    # Connect switches s1 and s2
    net.addLink(s1, s2)
    
    # Build the network
    net.build()
    
    # Configure IP addresses for h1
    h1.setIP(intf="h1-eth0", ip='192.168.45.2/24')
    
    # Configure IP addresses for h3
    h3.setIP(intf="h3-eth0", ip='192.168.45.235/24')
    
    # Configure IP addresses for h2
    h2.setIP(intf="h2-eth0", ip='192.168.45.143/24')
    h2.setIP(intf="h2-eth1", ip='192.168.45.156/24')
    
    # Start the network
    net.start()
    
    # Drop into CLI mode
    CLI(net)
    
    # Stop the network
    net.stop()


if __name__ == '__main__':
    setLogLevel('info')
    myTopo()
