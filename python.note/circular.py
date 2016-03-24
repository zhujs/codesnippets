# coding: utf-8
"""
A demo that shows circular references problem in Python
"""
class A(object):
    def __init__(self, b_instance):
        self.b = b_instance
        #self.b = weakref.ref(b_instance) # weak reference

class B(object):
    def __init__(self):
        self.a = A(self)
    def __del__(self):
        # The destructor (the __del__ method) marks this item as "uncollectable", it may create a potential memory leak, see gc.garbage
        # Python doesn’t collect such cycles automatically because, in general, it isn’t possible for Python to guess a safe order in which to run the __del__() methods.
        print "__del__ method"

def test():
    b = B()

test()

import gc

# The garbage collector supplements the reference counting already 
# used in Python, you can disable the collector if you are sure your 
# program does not create reference cycles

# solution: weak references or with statement
gc.collect()
print gc.garbage, len(gc.garbage)

# explicitly remove the circle
del gc.garbage[0].a

# remove references in the gc.garbage list
del gc.garbage[:]


# create a circular reference with the stack frame and the local variable.
def main():
    try:
        raise Exception('here')
    except:
        pass

    # (exceptionType , value, traceback )
    exc_info = sys.exc_info()
    import objgraph
    objgraph.show_backrefs([exc_info, main])
    #solution: 
    #del exc_info[2]
