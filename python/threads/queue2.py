import time
import threading
import random
import Queue

NUM_ELEMENTS_TO_PROCESS = 10

NUM_WORKER_THREADS = 2

#note that exclusive access to this object MUST be guaranteed
#if more than one thread is to write on the same location
sharedArray = list(xrange(NUM_ELEMENTS_TO_PROCESS))

def do_work(item):
  print "thread ", threading.currentThread(), "processing item", item
  sharedArray[item] = item*item;
  time.sleep(random.randint(1,3))

def worker(): 
  while True:
    try:
      item = q.get(False)
    except Queue.Empty:
      break;
    do_work(item) 
    q.task_done() 


q = Queue.Queue() 

for e in xrange(NUM_ELEMENTS_TO_PROCESS):
    q.put(e) 

print "before:", sharedArray

for thr in xrange(NUM_WORKER_THREADS): 
    t = threading.Thread(target=worker)
#    t.setDaemon(True)
    t.start() 

q.join()       # block until all tasks are done
print "after:", sharedArray
