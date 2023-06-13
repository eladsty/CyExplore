import pyfiglet
import sys
import socket
from datetime import datetime

ascii_banner = pyfiglet.figlet_format("PORT SCANNER")
print(ascii_banner)

if len(sys.argv) == 2:	
	target = sys.argv[1] #the ip to scan
else:
	print("Invalid amount of Argument, enter ip to scan")

print("-" * 50)
print("Scanning Target: " + target)
print("Scanning started at:" + str(datetime.now()))
print("-" * 50)

try:	
	for port in range(1,65535):
		#AF_INET is the address familly SOCK_STREAM is the sock type
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		
		# check if port is open with connect_ex func
		result = s.connect_ex((target,port))
		if result == 0:
			print("Port {} is open".format(port))
		s.close()
		
except KeyboardInterrupt:
		sys.exit()
except socket.gaierror:
		print("\n Hostname Could Not Be Resolved !!!!")
		sys.exit()
except socket.error:
		print("\ Server not responding !!!!")
		sys.exit()
