# coding: utf-8
# A generator will provide performance benefits only if we do not intend to use that set of generated values more than once
# Build and return a list
def firstn(n):
    """return first n integers, builds the full list in memory"""
    num, nums = 0, []
    while num < n:
        nums.append(num)
        num += 1
    return nums

sum_of_first_n = sum(firstn(1000000))



# Using the generator pattern (an iterable)
class firstn(object):
    """An iterable object that is required to support the iterator protocol"""
    def __init__(self, n):
        self.n = n
        self.num, self.nums = 0, []

    def __iter__(self):
        """return the iterator object itself"""
        return self

    # Python 3 compatibility
    def __next__(self):
        return self.next()

    def next(self):
        if self.num < self.n:
            cur, self.num = self.num, self.num+1
            return cur
        else:
            raise StopIteration()

sum_of_first_n = sum(firstn(1000000))

#_iter_ = obj.__iter__()  
#while True:  
#    try:  
#        x = _iter.next()  
#    except StopIteration:  
#        break  
#    ...

# a generator that yields items instead of returning a list
# generator makes building iterators easy
def firstn(n):
    """It is very similar to the implementation that built a list in memory, but has the memory usage characteristic of the iterator implementation"""
    num = 0
    while num < n:
        yield num
        num += 1

sum_of_first_n = sum(firstn(1000000))
