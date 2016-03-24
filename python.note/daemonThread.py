# coding: utf-8

import time
import sys,os
import thread,threading

def func():
    try:
        time.sleep(1)
        thread.exit()
        print 'Never reach here'
    except SystemExit as e:
        print 'SystemExit gets caught in ' + threading.currentThread().getName()

	
# create a non-daemon thread by default (th.setDaemon())
#   http://blog.csdn.net/yueguanghaidao/article/details/40088431
th = threading.Thread(target=func)

# th.run() will invoke the function in the calling thread
th.start()

# a low-level method to create daemon threads
#thread.start_new_thread( func ,tuple() )

print threading.currentThread().getName() + ' exits'
sys.exit() # is similar to thread.exit()
