import scapy.all as scapy
import sys
 

def UpdateGateway():
    
def main(victim_ip):
    att_MAC = scapy.Ether().src
    fake_packet = IP(ttl=64)
    fake_packet.src = "10.1.0.1"
    fake_packet.dst = victim_ip
    sendp(fake_packet)


# I should add to the packet that my
print(main("10.1.0.174"))