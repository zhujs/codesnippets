# coding: utf-8


flist = []  
# 如果在一个内部函数里，对外部作用域（但不是在全局作用域，如下面的变量i）的变量进行引用，那么该内部函数就被认为是闭包(closure)
# 闭包=函数块+定义函数时的环境
# 闭包不能修改外部变量的值（对i赋值）
for i in range(3):  
    def foo(x): print x + i
    #solution: def foo( x , i = i ), output will be 2, 3, 4
    flist.append(foo)  


# the variables used in the closures will be evaluated when the closure is called (i in this example and i is 2 now) 
# 
for f in flist:
    f(2)  # i = 2 when this is called

# so output will be 4, 4, 4


# 用途1，当闭包执行完后，仍然能够保持住当前的运行环境（可以对外部引用的变量作持续变更）
# 用途2，闭包可以根据外部作用域的局部变量来得到不同的结果，这有点像一种类似配置功能的作用，我们可以修改外部的变量，闭包根据这个变量展现出不同的功能。 
