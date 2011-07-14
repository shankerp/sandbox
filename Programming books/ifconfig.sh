sudo ifconfig eth0 192.168.112.226 netmask 255.255.255.0
sudo route add default gw 192.168.112.1
sudo killall vpnc
echo "nameserver 192.168.112.1" | sudo tee /etc/resolv.conf
sudo vpnc
