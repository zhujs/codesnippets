# coding: utf-8
# what happens if multiple threads write to sys.stdout?
# sys.stdout.write() is thread-safe
import threading, sys
import time,signal


class WriteThread(threading.Thread):
    def __init__(self,message="hello, there"):
        super(WriteThread, self).__init__()
        self.outstream = sys.stdout
        self.message = message

    def run(self):
        while True:
            #print self.message # not thread-safe
            self.outstream.write(self.message + '\n')


# set SIGINT's handler to default
signal.signal(signal.SIGINT, signal.SIG_DFL)

writeThread1 = WriteThread()
writeThread2 = WriteThread("What are you doing right now? Mr.J")


writeThread1.start()
writeThread2.start()
writeThread1.join()
writeThread2.join()

def sigintHandler(sig, frame):
    print "SIGINT got caught"

#signal.signal(signal.SIGINT, sigintHandler)


while True:
    time.sleep(5)
