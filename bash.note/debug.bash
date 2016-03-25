# 1. 使用trap命令，捕捉“伪信号”

ERRTRAP ()
{
    echo "[ LINE:$1 ] Error: Command or function exited with status $?"
}

foo ()
{
    return 1;
}

# ERR：命令退出状态不为0时，其相应的命令被执行
trap 'ERRTRAP $LINENO' ERR

# DEBUG：在每条命令执行前，其相应的命令被执行
trap 'echo "$LINENO, var=$var"' DEBUG

# RETURN：函数或source命令执行后，其相应的命令被执行

# EXIT：脚本退出时，其命令被执行


# 2. 使用tee命令捕捉管道的中间输出
ipaddr=$(ifconfig | grep 'inet addr:' | grep -v '127.0.0.1'| tee temp.txt | cut -d : -f3 | awk '{print $1}')



# 3. debug hook
DEBUG()
{
    if [ "$DEBUG" = "true" ]; then
        "$@"
    fi
}

var=1
DEBUG echo "var=$var"



# 4. shell选项
# -n 只读取shell脚本，但不实际执行
# -x 进入跟踪方式，显示所执行的每一条命令
# -c "string" 从strings中读取命令
DEBUG set -x    # 启动"-x"选项

# 定制PS4变量，开启-x选项后，输出更多的调试信息
export PS4='+ { $LINENO : ${FUNCNAME[0]} } '


# 5. 使用bashdb
