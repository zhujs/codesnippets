# coding: utf-8

class DataDesc(object):
	"A data descriptor example that just demonstrates the protocol"
    
	def __get__(self, obj, cls=None):
		pass

	def __set__(self, obj, val):
		pass

	def __delete__(self, obj):
		pass

class NonDataDesc(object):
	"A non-data descriptor example that just demonstrates the protocol"
    
	def __get__(self, obj, cls=None):
		pass

class WithDataDescClass(object):
	dataDesc = DataDesc()
	attr1 = "class attr"

class WithNonDataDescClass(object):
	nonDataDesc = NonDataDesc()
	attr1 = "class attr"

"""
Descriptor是用来定制“访问类或其实例的成员”的一种协议，必须用于类中。
假设d的类型为DataDesc，obj类型为WithDataDescClass
    # 相当于调用了d.__get__(obj, type(obj))
    x = obj.d

    # 相当于调用了d.__get__(None,type(obj)) 
    x = WithDataDescClassData.d

当使用类来引用Descriptor时，只有__get__会调用（如print WithDataDescClass.d），
WithDataDescClass.d = "test" 会把Descriptor替换掉（删除操作也一样）


Data descriptors are useful for providing full control over an attribute.
Non-data descriptors, in contrast, only provide a value when an instance itself does not have a value (function object in Python).

属性查找步骤：
    1. If attrname is a special (i.e. Python-provided) attribute for objectname, return it (__doc__).

    2. Check objectname.__class__.__dict__ for attrname. If it exists and is a data-descriptor, return the descriptor result. Search all bases of objectname.__class__ for the same case.

    3. Check objectname.__dict__ for attrname, and return if found. If objectname is a class, search its bases too. If it is a class and a descriptor exists in it or its bases, return the descriptor result.

    4. Check objectname.__class__.__dict__ for attrname. If it exists and is a non-data descriptor, return the descriptor result. If it exists, and is not a descriptor, just return it. If it exists and is a data descriptor, we shouldn't be here because we would have returned at point 2. Search all bases of objectname.__class__ for same case.

    5. Raise AttributeError 
"""

objData =WithDataDescClass()
objNonData = WithNonDataDescClass()

# Check objectname.__class__.__dict__ for attrname. If it exists and is a data-descriptor, use the descriptor to set the value. Search all bases of objectname.__class__ for the same case, otherwise, insert into objectname.__dict__
objNonData.nonDataDesc = 2 # insert into objNonData.__dict__
print objData.__doc__ # step 1
print objData.dataDesc # step 2
print objNonData.nonDataDesc # step 3, in objNonData.__dict__, hide the non-data descriptors
del objNonData.nonDataDesc
print objNonData.nonDataDesc # step 4 


# User-defined function in class is a non-data descriptor.
# we can hide it using a function (step 3)

# Implicit invocations of special methods are only guaranteed to work 
# correctly if defined on an object’s type, not in the object’s instance 
# dictionary. 

# If it did go to the instance then even something like str(C) 
# (str of the class C) would go to C.__str__(), which is a method
# defined for an instance of C, and not C itself

# Implicit special method lookup generally also bypasses the 
# __getattribute__() method even of the object’s metaclass

# More information in:
#   https://docs.python.org/2/reference/datamodel.html#new-style-special-lookup 

class C(object):
    def __len__(self):
        return 0

cobj = C()

def mylen():
    return 1

cobj.__len__ = mylen
print cobj.__len__() # invokes cobj.__dict__.__len__() (mylen) 
print len(cobj) # always invokes C.__dict__.__len__() 

"""
# solution:
class C(object):
    def __len__(self):
        return self._mylen()

    def _mylen(self):
        return 0

cobj = C()

def mylen():
    return 1

cobj._mylen = mylen
print len(cobj)  
"""
