## ${var} 		变量var的值, 与$var相同

var=3
ref=var
# 注意!号表示间接引用（除了${!prefix*}与${!name[@]}）
echo ${!ref}
  	 
# 返回默认值
## ${var-DEFAULT} 	如果var没有被声明, 那么就以$DEFAULT作为其值
## ${var:-DEFAULT} 	如果var没有被声明, 或者其值为空, 那么就以$DEFAULT作为其值
  	 
# 设置默认值
## ${var=DEFAULT} 	如果var没有被声明, 那么就以$DEFAULT作为其值并设置变量
## ${var:=DEFAULT} 	如果var没有被声明, 或者其值为空, 那么就以$DEFAULT作为其值并设置变量
  	 
# 测试变量存在 
## ${var+OTHER} 	如果var声明了, 返回$OTHER, 否则就为null字符串
## ${var:+OTHER} 	如果var被声明且非空, 返回$OTHER, 否则返回null字符串
  	 
# 捕捉错误
## ${var?ERR_MSG} 	如果var没被声明, 那么就打印$ERR_MSG *
## ${var:?ERR_MSG} 	如果var没被声明或其值为null, 那么就打印$ERR_MSG，并退出脚本
  	 
# 以下两个表达式返回的是所有变量名的字符串
## ${!varprefix*} 	匹配之前所有以varprefix开头进行声明的变量
## ${!varprefix@} 	匹配之前所有以varprefix开头进行声明的变量


## ${#string}		$string的长度
## ${#array[@]}     数组元素个数

## ${!name[@]}
## ${!name[*]}      数组的key列表，或是0（name存在且非数组），null
  	 
# 字符串切片及获得子数组
## ${string:position} 	在$string中, 从位置$position开始提取子串
## ${string:position:length} 	在$string中, 从位置$position开始提取长度为$length的子串
  	 
# 删除开头或结尾字符串
## ${string#substring} 	从string开头删除最短匹配$substring的子串
## ${string##substring}	从string开头删除最长匹配$substring的子串
## ${string%substring} 	从string结尾删除最短匹配$substring的子串
## ${string%%substring}	从string结尾删除最长匹配$substring的子串


## ${string/substring/replacement}      代替第一个匹配的$substring
## ${string//substring/replacement} 	代替所有匹配的$substring
## ${string/#substring/replacement} 	代替string开头的$substring
## ${string/%substring/replacement} 	代替string结尾的$substring

# '#' 匹配开头，'%' 匹配结尾


## ${parameter^pattern}
## ${parameter^^pattern}
## ${parameter,pattern}
## ${parameter,,pattern}
## 转换大小写
