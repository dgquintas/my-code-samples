from __future__ import with_statement
import threading
import random
from time import sleep, time

NUM_PHILOSOPHERS = 5

class Chopsticks:
  def __init__(self):
    self.chopsticks = [True for i in range(NUM_PHILOSOPHERS)]
    self.evnt = threading.Event()
    self.lock = threading.Lock()

  def pickUp(self, i):
    with self.lock:
      if not self.chopsticks[i]:
        self.lock.release()
        self.evnt.wait(0.5)
        self.lock.acquire()
      if not self.chopsticks[i]:
        return False
      
      #else, the i-th chopstick is available: get it
      assert( self.chopsticks[i] == True )
      self.chopsticks[i] = False
      return True

  def putDown(self, i):
    with self.lock:
      assert(self.chopsticks[i] == False)
      self.chopsticks[i] = True
      self.evnt.set()
      self.evnt.clear()
      assert(self.chopsticks[i] == True)

class Philosopher(threading.Thread):

  def __init__(self, i, cs):
    threading.Thread.__init__(self, name="Philosopher " + `i`)
    self.i = i
    self.stop = False
    self.cs = cs
    self.lastLunch = 0


  def terminate(self):
    self.stop = True

  def think(self):
    sleep(random.uniform(1, 1.5));

  def sitDown(self):
    pass

  def pickChopsticks(self):
    while True:
      secondCS =  (self.i + 1) % NUM_PHILOSOPHERS
      hasLeftCS = self.cs.pickUp(self.i)
      if self.i % 2 == 0:
        sleep(0.5)
      hasRightCS = self.cs.pickUp(secondCS)
      hasBoth = hasLeftCS and hasRightCS
      if not hasBoth:
        if hasLeftCS:
          self.cs.putDown(self.i)
        elif hasRightCS:
          self.cs.putDown(secondCS)
      else: #we have both
        break

  def eat(self):
    sleep(random.uniform(0.5, 1.0));
    self.lastLunch = time()

  def standUp(self):
    self.cs.putDown(self.i);
    self.cs.putDown( (self.i + 1) % NUM_PHILOSOPHERS )

  def run(self):
    activities = [self.think, 
                  self.sitDown, 
                  self.pickChopsticks, 
                  self.eat, 
                  self.standUp]
    while not self.stop:
      for activity in activities:
        print "Philosopher %d %ss" % (self.i, activity.__name__)
        activity()

def checkStarvation(philosophers, threshold):
  print "checking starvation status..."
  numStarving = 0
  for philosopher in philosophers:
    fastLength = (time() - philosopher.lastLunch)
    if fastLength > threshold:
      print "Philosopher %d is starving (%f)" % (philosopher.i, fastLength) 
      numStarving += 1
  return numStarving


def main():
  random.seed(0)
  chopsticks = Chopsticks()
  philosophers = [Philosopher(i,chopsticks) for i in range(5)]

  for philosopher in philosophers:
    philosopher.start()

  while True:
    sleep(5)
    checkStarvation(philosophers, 5)

if __name__ == '__main__':
  main()


