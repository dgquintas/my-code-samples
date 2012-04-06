from twisted.internet.task import LoopingCall
from twisted.internet import reactor
from time import time, sleep

def f():
  print "hello %d" % time()

def stopCB(loopingCallSelf):
  print "c'est fini, %s" % str(loopingCallSelf)

lc = LoopingCall(f)
d = lc.start(2, now=False)
d.addCallback(stopCB)

reactor.callLater(6, lc.stop)
reactor.run()



