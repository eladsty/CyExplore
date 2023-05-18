from scapy.all import *
from scapy.layers.l2 import Ether 

import sys
from time import sleep


# I should add to the packet that my
print( getmacbyip("10.1.0.133") )