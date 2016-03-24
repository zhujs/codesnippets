import copy
import random
import memory_profiler

# python -m memory_profier memory.py

@memory_profiler.profile
def function():
    x = range(1000000)  # allocate a big list
    y = copy.deepcopy(x)
    del x
    return y

if __name__=="__main__":
    function()

