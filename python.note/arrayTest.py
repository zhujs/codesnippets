# coding: utf-8
import array

from timeit import Timer
 
def arrayTest():
    # create and int array
    a = array.array("i", [1, 2, 3, 4, 5])

    # create an array with the generator
    b = array.array(a.typecode, (2 * x for x in a))

def enumerateTest():
    a = array.array("i", [1, 2, 3, 4, 5])
    for i, x in enumerate(a):
        a[i] = 2 * x

if __name__=='__main__':
    m = Timer("arrayTest()", "from __main__ import arrayTest")
    n = Timer("enumerateTest()", "from __main__ import enumerateTest")

    print m.timeit()
    print n.timeit()
