import gevent
import random

class Periodic(object):
    def __init__(self, period, i):
        self.period = period
        self.i = i 

    def _run(self):
        print "Yo wassup, %d" % self.i

periodics = [ Periodic(1, i) for i in range(10) ]
for p in periodics:
    p.start()

gevent.joinall(periodics)
