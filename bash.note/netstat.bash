
# list out all connections from different protocols 
netstat -a

# To list out only tcp connections: -t
netstat -at

# To list out only udp connections: -u
netstat -au

# disable reverse dns lookup for faster output: -n
netstat -ant

# list out only listening connections: -l
netstat -nlt

# get the process name/pid and user id: -p, -e
netstat -nlpt

# To list out statistics of all packet types: -s
netstat -s

# Display kernel routing information: -r
netstat -rn


# Print network interfaces: -i, -e
netstat -ie 

# Display multicast group information for IPV4 and IPV6: -g
netstat -g
