import time
import threading
import random
import Queue

def do_work(item):
  print "thread ", threading.currentThread(), item
  #time.sleep(random.randint(1,3))
  time.sleep(2)

def worker(): 
  while True:
    try:
      item = q.get(False) # no blocking
    except Queue.Empty:
      break;
    do_work(item) 
    q.task_done() 

q = Queue.Queue() 

def source():
  for i in xrange(100):
    yield i

num_worker_threads = 50

for item in source():
    q.put(item) 

for i in range(num_worker_threads): 
    t = threading.Thread(target=worker)
#    t.setDaemon(True)
    t.start() 


q.join()       # block until all tasks are done
