if [ $# -lt 2 ] then
  echo "Usage: $0 <connect'd-iface> <nat'd-iface>"
  exit 1
fi

echo 1 | sudo tee -a /proc/sys/net/ipv4/ip_forward
sudo iptables -t nat -A POSTROUTING -o $1 -j MASQUERADE
sudo iptables -A FORWARD -i $1 -o $2 -m state --state RELATED,ESTABLISHED -j ACCEPT
sudo iptables -A FORWARD -i $2 -o $1 -j ACCEPT

