# encoding: utf-8

# Different string formatting API for Python
#       https://pyformat.info/ 
# 
# New-style format
#   https://docs.python.org/2.7/library/string.html#format-string-syntax

print "%s %s" % ("one", "two")
print "{} {}".format("one", "two")
print "{0} {1}".format("one", "two")


class Data(object):
    def __str__(self):
        return 'str()'

    def __repr__(self):
        return 'repr()'

# use str() and repr()
print '%s %r' % (Data(), Data())
print '{0!s} {0!r}'.format(Data())


# Truncationg and padding 
print '%-10.5s' % ('xylophone',)
print '{:10.5}'.format('xylophone') # equivalent to '{:<10.5}'.format('xylophone')
print '{:>10.5}'.format('xylophone')
print '{:_<10.5}'.format('xylophone') # specify the padding character 
print '{:^10.5}'.format('xylophone')  # center align

print '%06.2f' % (3.141592653589793,)
print '{:06.2f}'.format(3.141592653589793)
print '%+d' % (42,)
print '{:+d}'.format(42)
print '{: d}'.format(42)
print '{: d}'.format(-42)
print '{:=15d}'.format((-23)) # control the position of the sign symbol relative to the padding


# Named placeholders
data = {'first': 'Hodor', 'last': 'Hodor!'}
print '%(first)s %(last)s' % data
print '{first} {last}'.format(**data)
print '{first} {last}'.format(first='Hodor', last='Hodor!')



# Getitem and Getattr
print '{d[first]} {d[last]}'.format(d=data) # __getitem__

data = [1, 2, 3, 4]
print '{d[1]} {d[2]}'.format(d=data) # __getitem__

class Plant(object):
    type = 'tree'
    kinds = [{'name': 'oak'}, {'name': 'maple'}]

print '{p.type}: {p.kinds[0][name]}'.format(p=Plant())


# Datetime
from datetime import datetime

print '{:%Y-%m-%d %H:%M}'.format(datetime(2001, 2, 3, 4, 5))



# Parametrized formats
print '%.*s = %.*f' % (3, 'Gibberish', 3, 2.7182)
print '%*.*f' % (5, 2, 2.7182)

print '{:{align}{width}}'.format('test', align='^', width='10')
print '{:.{prec}} = {:.{prec}f}'.format('Gibberish', 2.7182, prec=3)
print '{:{width}.{prec}f}'.format(2.7182, width=5, prec=2)

# 有效数字，相当于{:g}
print '{:{prec}} = {:{prec}}'.format('Gibberish', 2.7182, prec='.3') 

dt = datetime(2001, 2, 3, 4, 5)
print '{:{dfmt} {tfmt}}'.format(dt, dfmt='%Y-%m-%d', tfmt='%H:%M')
print '{:{}{}{}.{}}'.format(2.7182818284, '>', '+', 10, 3)
print '{:{}{sign}{}.{}}'.format(2.7182818284, '>', 10, 3, sign='+')


# Custom objects
class HAL9000(object):
    def __format__(self, format):
        if (format == 'open-the-pod-bay-doors'):
            return "I'm afraid I can't do that."
        return 'HAL 9000'

print '{:open-the-pod-bay-doors}'.format(HAL9000())
