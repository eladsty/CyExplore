#!/bin/bash
sudo ip route flush table main
sudo systemctl restart NetworkManager
sudo ip route add default via 192.168.56.1 dev anp0s3