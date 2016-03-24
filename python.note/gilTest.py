# coding: utf-8
import time
import sys, threading


def countdown(n):
    while n > 0:
        n -= 1
COUNT = 100000000

start_time = time.time()
countdown(COUNT)
print "--- Sequential Countdown in Python 2.7 : %s seconds ---" % (time.time() - start_time)


start_time = time.time()
t1 = threading.Thread(target=countdown,args=(COUNT//2,))
t2 = threading.Thread(target=countdown,args=(COUNT//2,))
t1.start(); t2.start()
t1.join(); t2.join()
print "--- Parallel (hopefully) Countdown in Python 2.7 : %s seconds ---" % (time.time() - start_time)
