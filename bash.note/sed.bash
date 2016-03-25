# 删除第一行
echo -e "number1\nnumber2" | sed '1d'

# 在第一行后添加数据
# 类似命令c(change), i(insert)
echo -e "number1\nnumber2" | sed '1a number3'

# 替换每二行
echo -e "number1\nnumber2" | sed '2s/.*/number3/'

# 搜索，输出所有行及匹配行
echo -e "number1\nnumber2" | sed '/2/p'

# 搜索并只打印匹配行，执行完到第二行后退出
echo -e "number1\nnumber2" | sed -n '/2/p;/2/q'

# 来一个复杂的，删除文件最后10行数据
sed -e :a -e '$d;N;2,10ba' -e 'P;D'

# /2/d 搜索并删除
# /2/{s/number/num/;p} 搜索并执行命令
