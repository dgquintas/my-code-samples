from __future__ import print_function
import time
import multiprocessing
import threading
try:
    import queue
except:
    import Queue as queue

import logging

logging.basicConfig(level=logging.INFO, format='[%(process)d] %(asctime)s %(levelname)s: %(message)s')

logger = logging.getLogger()

qrun = multiprocessing.Queue()
qtime = queue.PriorityQueue()

e = threading.Event()

class Task(object):
    def __init__(self, delay, f, args):
        self.delay = delay
        self.original_delay = delay
        self.f = f
        self.args = args

    def __cmp__(self, other):
        if self.delay < other.delay:
            return -1
        elif self.delay > other.delay:
            return +1
        else:
            return 0

    def __repr__(self):
        return "Task with delay %s and args '%s'" % (self.delay, self.args)

def f(i):
    print(time.asctime(), "Task", i)
    pass

# from main thread/process
def submit(task):
    logger.info("Submitting task '%s'", task)
    qtime.put((task, time.time()))
    e.set()

# thread
def timer():
    def light_sleep(t):
        " Returns number of seconds slept "
        logger.debug("Light-sleeping for %s seconds", t)
        starttime = time.time()
        if e.wait(t):
            # woken up by e.set, clean it
            logger.debug("Event was set. Cleaning it")
            e.clear()
        endtime = time.time()
        return endtime - starttime

    while True:
        logger.debug("Waiting for stuff at timer")
        (task, enq_time) = qtime.get()
        logger.debug("Got stuff at timer! %s", task)

        time_spent_in_q = time.time()-enq_time
        time_slept = light_sleep(task.delay - time_spent_in_q)
        logger.debug("Woke up from light_sleep after %s secs", time_slept)
        remaining_time = task.delay - time_spent_in_q - time_slept
        
        # we woke up. we either slept for min_delay
        # or have been awoken by a new task. 
        if remaining_time <= 0: # we slept unperturbed
            # send task to the runner
            logger.debug("Submitting task '%s' to runner", task)
            qrun.put(task)

        else: # sth woke us up. Maybe the new task is due before remaining_time
            # enqueue current task with updated delay to remaining_time and
            # let's leave it to the prioq to decide who comes first
            logger.debug("Re-enqueuing task with delay from %s to %s", task.delay, remaining_time)
            task.delay = remaining_time
            qtime.put((task, time.time()))

# process.
def runner():
    while True:
        task = qrun.get()
        f, args = task.f, task.args
        logger.info("Running task '%s'", task)
        f(*args)


if __name__ == '__main__':
    timer_thread = threading.Thread(target=timer)
    runner_proc = multiprocessing.Process(target=runner)

    timer_thread.start()
    runner_proc.start()



#    submit( Task(0.1, f, (".1 sec", )) )
    submit( Task(5, f, ("5 sec", )) )
    submit( Task(1, f, ("1 sec", )) )
    submit( Task(2, f, ("2 sec", )) )
#
#    print("Sleeping for 10 secs...")
#    time.sleep(10)
#    print("There we go again")
#    submit( Task(2, f, ("2 sec", )) )
#    submit( Task(2.1, f, ("2.1 sec", )) )
#    submit( Task(2.2, f, ("2.2 sec", )) )
#    submit( Task(2.3, f, ("2.3 sec", )) )
#
#
#    tasks = [Task(i/10.0, f, (i,)) for i in range(100,1,-1)]
#    for t in tasks:
#        submit(t)
#

