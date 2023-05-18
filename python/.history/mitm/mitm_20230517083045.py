import scapy.all as scapy
import sys
 
att_MAC = scapy.Ether().src
def ArpTest(victim_ip):
    vic_mac = mac = getmacbyip("victim_ip")

