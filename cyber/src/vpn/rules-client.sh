#!/bin/bash
sudo ip route flush table main
sudo systemctl restart NetworkManager
sudo ip route add default via 192.168.1.30 dev anp0s3