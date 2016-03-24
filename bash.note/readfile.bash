while read line
do
    ip=$(echo $line | sed s/[[:space:]]//g | awk -F ':' '{print $2}')
    port=$(echo $line | sed s/[[:space:]]//g | awk -F ':' '{print $3}')
    echo "telnet $ip $port !"

    # 如果不重定向标准输入，那么标准输入就会是：$1
    # 在while循环里面的其它交互命令也是如此！！
    telnet "$ip" "$port" < /dev/tty
done < $1
