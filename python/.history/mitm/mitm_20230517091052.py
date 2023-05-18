import scapy.all as scapy
import sys
 
att_MAC = scapy.Ether().src
 
def main(victim_ip):
    fake_packet = IP(ttl=64)
    fake_packet.src = "10.1.0.174"
    fake_packet.dst = victim_ip
    return att_MAC


print(main("10.1.0.174"))