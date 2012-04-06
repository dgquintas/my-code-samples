import multiprocessing
import time
import random
from pprint import pformat

class Child(multiprocessing.Process):
    def __init__(self, name, d):
        multiprocessing.Process.__init__(self, name=name)
        self.d = d

    def run(self):
        while True:
            t = random.randint(1,5)
            print("At process %s sleeping for %d" % (self.name, t))
            l = d.get(self.name, [])
            l.append(t)
            d[self.name] = l
            time.sleep(t)

mgr = multiprocessing.Manager()
d = mgr.dict()
children = [ Child("Child-%d"%i, d) for i in range(5)]
#for c in children:
#    d[c.name] = []

for c in children:
    c.start()
 
while True:
    time.sleep(1)
    print("At master. Dict: %s" % pformat(str(d)))



