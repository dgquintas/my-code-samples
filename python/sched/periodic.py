# http://www.doughellmann.com/PyMOTW/sched/
# The sched module implements a generic event scheduler for running tasks at
# specific times. The scheduler class uses a time function to learn the current
# time, and a delay function to wait for a specific period of time. The actual
# units of time are not important, which makes the interface flexible enough to
# be used for many purposes.

# The time function is called without any arguments, and should return a number
# representing the current time. The delay function is called with a single
# integer argument, using the same scale as the time function, and should wait
# that many time units before returning. For example, the time.time() and
# time.sleep() functions meet these requirements.

# To support multi-threaded applications, the delay function is called with
# argument 0 after each event is generated, to ensure that other threads also
# have a chance to run.

import sched, time, random

s = sched.scheduler(time.time, time.sleep)

class PeriodicTask(object):
    def __init__(self, scheduler, period, task):
        self._scheduler = scheduler
        self._period = period
        self._event = None
        self._task = task
        self._iterations = 0

    def start(self):
        self._event = self._scheduler.enter(0, 0, self._action, ())

    def _action(self):
        self._event = self._scheduler.enter(self._period, 0, self._action, ())
        self._task()
        self._iterations += 1
        # cancel ourselves after 10 iterations
        if self._iterations == 10:
            self.cancel()

    def cancel(self):
        self._scheduler.cancel(self._event)

def f(i):
    def _f():
        time.sleep(random.random()/1000.0)
        print "Task %d" % i
    return _f

tasks = [ PeriodicTask(s, random.randint(1,10), f(i)) for i in range(2000) ]
for task in tasks:
    task.start()

s.run()




