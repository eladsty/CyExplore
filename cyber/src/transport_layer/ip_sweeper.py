import sys
import socket
from datetime import datetime
import ipaddress

def ip_scanner(): 
    if len(sys.argv) == 3:	
        target_port = sys.argv[1]#the port to scan
        target_ip = sys.argv[2] #ip to scan *should be used with subnet 8 or 08
    
    else:
        print("Invalid amount of Argument, enter ip to scan")

    print("Scanning Target")
    ip_range = [str(ip) for ip in ipaddress.IPv4Network(target_ip)]
    for ip in ip_range:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)   
        s.settimeout(0.01)
        
        result = s.connect_ex((ip, int(target_port)))
        if result == 0:
            print(f"Port is open on {ip}")
        s.close()
        
ip_scanner()


# python3 ip_sweeper.py 22 10.1.0.0/24
