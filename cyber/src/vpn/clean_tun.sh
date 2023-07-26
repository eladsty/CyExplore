sudo ifconfig tun0 down
sudo ip link set tun0 down
sudo ip link delete tun0
sudo systemctl restart systemd-networkd
sudo ip addr flush dev enp0s3
