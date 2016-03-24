# coding: utf-8
import weakref
import gc

class MyObject(object):
    def my_method(self):
        print 'my_method was called!'

obj = MyObject()

# r() will return None if no 'strong references' to real object
r = weakref.ref(obj) # weakref.proxy(obj)

gc.collect()

# r() allows you to access the object referenced
assert r() is obj 

# Let's change what obj references to
obj = 1 
gc.collect()

assert r() is None # no more 'strong references'
