# coding: utf-8
# http://www.cnblogs.com/zijin/p/3468802.html

print """
除法的取整分成三类：向上取整、向下取整、向零取整（截断取整）。
右移运算符相当于向下取整！！

(-a)/b == -(a/b) 对向上、向下取整不一定成立，对向零取整成立，
    -(5 / 3) = -2   （向上取整）
    -5 / 3 = -1     （向上取整）

因此C/C++采取向零取整。但Python取用向下取整
取模运算：a=b*q + r, a/b=q, a%b=r

在C中：         -5 % 3 == -2 (-5 = 3 * (-1) + -2) （向零取整）
在Python中：    -5 % 3 == 1  (-5 = 3 * (-2) + 1 ) （向下取整） 

当a为负，b为正，向下取整使得r与b的符号相同 0<= r < b；
    想像 25 % 24 => 24 * 1 + 1
         -2 % 24 => 24 * -1 + 22（24为一天的小时数）

当b为负时，向下取整同样使得r与b符号相同 0>= r > b 
"""