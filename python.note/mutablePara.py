# coding: utf-8
# Use mutable object as a default value
def func( data = [] ): 
	data.append( 1)
	print data

# When the "def" statement is executed, the default parameter values are evaluated
# In Python, function is an object, various components are available as attributes on the function object
#   func.func_defaults: the default parameters list
func() # output: [1]
func() # output: [1, 1]

# solution:
# def func( data = None ):
# 	if data is None:
# 		data = []
# 	data.append(1):
# 	print data


def func( count=1  ):
	count += 1
	print count


# In this case, the variable 'count' is an immutable object!! the statement 'count += 1' forces 'count' point to another object.
func() # output: [2]
func() # output: [2]


#a = 1
#print id(a)
#a = a + 1
#print id(a)
