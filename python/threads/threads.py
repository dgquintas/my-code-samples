import threading 
import random
import Queue
import time

q = Queue.Queue();

class ThreadTest(threading.Thread):
  id = 0
  def __init__(self):
      threading.Thread.__init__(self)
      ThreadTest.id += 1
      self.res = None

  def run(self):
    global q
    while True:
      try:
        elem = q.get_nowait()
      except Queue.Empty:
        break;
      try:
        exec elem
        self.res = result
      except:
        pass
      q.task_done()


def launch():
  threads = []
  num_threads = 10
  txt ="""
print "hola, soy", threading.currentThread()
result = "foobar"
time.sleep(5)
"""
  for i in xrange(10):
    q.put(txt)

  threads = []
  for i in xrange(num_threads):
    t = ThreadTest()
    threads.append(t)
    t.start()

  q.join()
  print "finished!"

  return threads

if __name__ == '__main__':
  threads = launch()
  for thread in threads:
    print thread.res
