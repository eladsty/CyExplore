import scapy.all as scapy
import sys
from time import sleep

def spoof():
    while(1):

        sleep(10)

def get_mac(ip):
    arp_request = scapy.ARP(ip)
    broadcast = scapy.Ether(dst ="ff:ff:ff:ff:ff:ff")
    arp_request_broadcast = broadcast / arp_request
    answered_list = scapy.srp(arp_request_broadcast, timeout = 5, verbose = False)[0]
    return answered_list[0][1].hwsrc

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