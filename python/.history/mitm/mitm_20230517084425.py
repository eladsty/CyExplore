import scapy.all as scapy
import sys
 
att_MAC = scapy.Ether().src
def ArpTest(victim_ip):
    vic_MAC = getmacbyip(victim_ip)
    return vic_MAC


print(ArpTest("10.1.0.174"))