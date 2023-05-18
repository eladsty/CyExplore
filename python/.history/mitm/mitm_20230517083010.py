import scapy.all as scapy
import sys
 
att_MAC = scapy.Ether().src
victim = mac = getmacbyip("10.0.0.1")
def ArpTest(victim_ip):

