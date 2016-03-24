# coding: utf-8

# list comprehension, different objects in the list
list1 = [[1,2] for _ in range(3)]
print 'list1 =', list1
list1[0][0] = 3
print 'list1 =', list1

# references in list2 all point to the same object
list2 = [ [1,2] ] * 3
print 'list2 =', list2
list2[0][0] = 3
print 'list2 =', list2

print '------------------------------------------------'

# generator comprehension (since Python 2.6+)
gener1 = ([1,2] for _ in range(3))
print 'gener1 =', gener1

print '------------------------------------------------'

# set (dict) comprehension (since Python 2.7+)
set1 = {n for n in range(3)} 
print 'set1 =', set1
dict1 = {n: n**2 for n in range(3)}
print 'dict1 =', dict1
