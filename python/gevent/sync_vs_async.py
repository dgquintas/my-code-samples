import gevent
import gevent.monkey 
gevent.monkey.patch_time() # turn time.sleep into gevent.sleep

import random
from datetime import datetime
import time

def task(pid):
    s = random.randint(0,5)
    time.sleep(s)
    print 'Task', pid, 'done after', s, 'seconds'

def synchronous():
    for i in range(1,10):
        task(i)

def asynchronous():
    greenlets = [gevent.spawn(task, i) for i in range(1,10)]
    gevent.joinall(greenlets)

print '%s - Synchronous:' % datetime.now()
before = time.time()
synchronous()
after = time.time()
print '%s - Synchronous:' % datetime.now()
print "It's taken %f secs" % (after-before)

print

print 'Execution of async batch will always take as long as',\
      'the longest task'
print '%s - Asynchronous:' % datetime.now()
before = time.time()
asynchronous()
after = time.time()
print '%s - Asynchronous:' % datetime.now()
print "It's taken %f secs" % (after-before)
