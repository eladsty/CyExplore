import scapy.all as scapy
import sys
 

def UpdateGateway(victim_ip, gate_ip = "10.1.0.1"):
    fake_packet = IP(ttl=64)
    fake_packet.src = gate_ip
    fake_packet.dst = victim_ip

def main(victim_ip, gate_ip = "10.1.0.1"):
    att_MAC = scapy.Ether().src
    fake_packet = IP(ttl=64)
    fake_packet.src = gate_ip
    fake_packet.dst = victim_ip
    sendp(fake_packet)


# I should add to the packet that my
print(main("10.1.0.174"))