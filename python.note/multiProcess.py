# -*- coding:utf-8 -*-  
  
import multiprocessing,time
import random, signal,sys
  
def counter():  
    cnt = 0
    for i in xrange(10000):  
        for j in xrange(i):  
            cnt += j
  
class SubProcess(multiprocessing.Process):  
    def __init__(self, name):
        multiprocessing.Process.__init__(self, name=name)
        signal.signal(signal.SIGQUIT, self.handler)
        
    def handler(self, signum, frame):  
        print >> sys.stderr, 'signal get caught'
        self.terminate() # terminate by sending SIGTERM
  
    def run(self):  
        i = 0
        while i < 4:  
            print self.name,'counting...'
            counter()
            print self.name,'finish'
            i += 1
  
if __name__ == '__main__':  
    pro = SubProcess('process-1')
    pro.start()
    pro.join()
    print 'all done'


