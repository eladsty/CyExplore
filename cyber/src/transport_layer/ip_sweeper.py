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
    net1 = raw_input('Enter the IP address')
    net2 = net1.split('.')
    a = '.'
    net3 = net2[0] + a + net2[1] + a + net2[2] + a
    stn1 = int(raw_input("enter the frist Number "))
    edn1 = int(raw_input("enter the last Number "))
    edn1 = edn1 + 1
    td1 = datetime.now()
    
    for ip in ip_range:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        result = s.connect_ex((ip, int(target_port)))
        if result == 0:
            print(f"Port is open on {ip}")
        s.close()
        
ip_scanner()
