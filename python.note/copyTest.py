# coding: utf-8
import copy, weakref

a = [1,2,3]
b = [4,5]

c = [a,b]

# Normal Assignment, a strong reference
d = c

assert( id(c) == id(d) )      # d is the same object as c
assert( id(c[0]) == id(d[0]) )# d[0] is the same object as c[0]

# Shallow Copy
d = copy.copy(c)

assert( id(c) != id(d) )       # d is now a new object
assert( id(c[0]) == id(d[0]) ) # d[0] is the same object as c[0]

# Deep Copy
d = copy.deepcopy(c)

assert( id(c) != id(d) )          # d is now a new object
assert( id(c[0]) != id(d[0]) )    # d[0] is now a new object

# Avoid problems with duplicating recursive data structures
#   https://pymotw.com/2/copy/#recursion-in-deep-copy
