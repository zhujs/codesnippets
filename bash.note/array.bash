# Bash中有两种一维数组：indexed array and associative array
# 感觉indexed array也是个associative array，因为竟然可以不连续。。

# 声明数组
declare -a indexedArray
declare -A associativeArray # 使用关联数组必须先声明

# 赋值，同样可以在上面声明中赋值
indexedArray[2]=2
indexedArray=(1 [2]=2 3 4) # indexedArray[1]为空
associativeArray=(["name"]="zhu" ["address"]="here")


#引用
echo ${indexedArray} # 即${indexedArray[0]
echo ${indexedArray[-1]} # 返回最后一个元素
echo ${associativeArray["name"]}
echo ${associativeArray[@]} # 跟${associativeArray[*]}的不同只在于是否在双引号中，参考"$*"与"$@"的不同
echo ${!associativeArray[@]} # 即${!associativeArray[*]}，返回Key序列} 

echo ${#indexedArray[*]} # 即${#indexedArray[@]}，返回数组个数
echo ${!indexedArray[@]} # 即${!indexedArray[*]}，返回下标序列} 


#删除变量
unset indexedArray
unset associativeArray["name"]

# The set and declare builtins display array values in a way that allows them to be reused as assignments.
