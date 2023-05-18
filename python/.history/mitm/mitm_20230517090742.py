import scapy.all as scapy
import sys
 
att_MAC = scapy.Ether().src
 
def main(victim_ip):
    return att_MAC


print(main("10.1.0.174"))