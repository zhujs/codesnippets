# coding: utf-8

# what if bar = [ 13 ]
bar = 13

# when Python executes the declaration statements, a function object was created
def foo():
    print bar
    bar = 0 # add bar to the list of local variable because it is an assignment statement

# throw exception: 'bar' referenced before assignment
foo()

def foo( arg ):
    if arg > 0: # Python doesn't know whether 'bar' has been referenced
        print bar
    bar = 0

# Use global keyword to avoid this or never use the global variables
def func():
    if True:
        string='hello'
    print string # access the variable declared in the if block (can't do this in C/C++)!!
