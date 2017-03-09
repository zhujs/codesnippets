# coding: utf-8

# http://www.cafepy.com/article/python_types_and_objects/python_types_and_objects.html
print """
Everything is object!! so the 'object' type is an object of type 'type', 'int' is an object of 'type', these are called Type Objects!!! 

'object' is the base of all other types!!
'object' is an instance of type 'type'
'object' is also the base type of type 'type'
class statement always creates a type object
use the call operator to create a type (with type(...)) or a non-type object

'__metaclass__' is used to specify the type (default is 'type') of the type objects! It must be a subclass of the "type of the base type object"! In the context of multi-inheritance, Python try to figure out the correct metaclass, otherwise, the __metaclass__ attrbute is required.
"""

# by calling str(object)
print "print object ==> ",object 

# object.__class__
print "print type(object) ==> ",type(object) 

print "print type(int) ==> ",type(int) 

print "print type(type) ==> ",type(type)

class Test(object):
    classAttr="class atrrbute"
    def func(self):
        return "function in Class"

print """
class Test(object):
    classAttr="class atrrbute"
    def func(self):
        return "function in Class"
"""

testObj=Test();
testObj.instanceAttr="instance attrbute"
print "testObj.instanceAttr:", testObj.instanceAttr, "in testObj.__dict__"
print "testObj.classAttr:", testObj.classAttr, "in testObj.__class__.__dict__"

# Some built-in types and their instances do not have a __dict__(lists, tuples, etc.).


print """
For old-style class, the statement x.__class__ is the class of object x, type(x) is always <type 'instance'>
"""

# more information in file: attributes.py
print "Test.func", Test.func
print "Test.__dict__['func']", Test.__dict__['func'], "unbound function in python!"
print "testObj.func", testObj.func, "bounds the func function in Test to the testObj object!!"

print """
Python creates testObj.func by calling Test.__dict__['func'].__get__(testObj,Test), creates Test.func by calling Test.__dict__['func'].__get__(None,Test) (so it's unbound method)
Such objects are called descriptors (non-data descriptors), work only when attached to classes.
"""
