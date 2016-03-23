# -*- coding: utf-8 -*-

"""
在多重继承中，Python使用MRO（Method Resolution Order）来决定
如何调用父类的方法。
在type object中，属性__mro__是包含该类型所有父类的tuple。
super对象相当于利用这个属性找到当前类型的前一个父类，并调用
父类中的方法
super对象也可以在类方法中使用
"""
class A(object):
    def say_hello(self):
        print 'A says hello'

class B(A):
    def say_hello(self):
        # super对象使用__getattribute__方法来查找say_hello属性
        # 使用slef的类型来获得__mro__属性
        super(B, self).say_hello() 
        print 'B says hello'

class C(A):
    def say_hello(self):
        super(C, self).say_hello()
        print 'C says hello'

class D(B, C):
    def say_hello(self):
        super(D, self).say_hello()
        print 'D says hello'

B.say_hello()
D.say_hello()

"""
super(type)返回一个Descriptor
class B(A):
    def do_your_stuff(self):
        self.__super.do_your_stuff()
        # do stuff with self for B

#Python是如何隐藏开头为双下划线的对象的。。
B._B__super = super(B) # 此时，B._B__super为一个Descriptor

# b._B__super = super(B)不能得到bound super object,
# 记住，Descriptor只能在type object中定义时有效，因此必须在B.__dict__中。
"""
