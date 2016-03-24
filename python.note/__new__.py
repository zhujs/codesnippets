# coding: utf-8

class A(object):
    def __new__(cls, *args):
        print "A __new__ method"
        print cls, args
        return super( A, cls).__new__(cls,args)

    def __init__(self, val):
        print "A __init__ method"
        print "value =", val

class B(A):
    def __new__(cls, *args):
        print "B __new__ method"
        print cls, args

        # args is passed to __init__ method
        # return an instance of cls (B), otherwise __init__ will not be invoked
        return super(B, cls).__new__(cls,args)

    def __init__(self, val):
        print "B __init__ method"
        print "value =", val

B(3)
