#!/bin/bash
sudo ip route flush table main
sudo systemctl restart NetworkManager
sleep 1
sudo ip route add default via 192.168.56.1
sudo mv res_conf /etc/resolv.conf