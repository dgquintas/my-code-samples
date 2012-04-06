# have a mapping with the task and its submission time. 
# a thread goes over this map/list periodically (with a certain granularity) 
# and sends to the runner process all those tasks that have been enqueued
# for > task_period seconds. The item's enqueue time is then updated to the 
# last time it was processed. 
from __future__ import print_function

try:
    import queue
except:
    import Queue as queue

import multiprocessing
import threading 
import time

import logging

logging.basicConfig(level=logging.INFO, format='[%(process)d] %(asctime)s %(levelname)s: %(message)s')

logger = logging.getLogger()

class Task(object):
    def __init__(self, period, f, args):
        self.period = period
        self.enq_t = None
        self.f = f
        self.args = args

    def __repr__(self):
        return "Task with period %s and args '%s'" % (self.period, self.args)

def f(i):
    pass

q = queue.Queue()
qrun = multiprocessing.Queue()

def submit(task):
    logger.info("Submitting task '%s'", task)
    task.enq_t = time.time()
    q.put(task)

# thread
def timer():
    tasks = []
    while True:
        try:
            task = q.get(block=True, timeout=0.01)
            tasks.append(task)
        except queue.Empty:
            pass

        t = time.time()
        # traverse task list checking for ripe ones
        for task in tasks:
            if t - task.enq_t >= task.period:
                qrun.put(task)
                task.enq_t = t

# process
def runner():
    while True:
        task = qrun.get()
        f, args = task.f, task.args
        logger.info("Running task '%s'", task)
        f(*args)

timer_thread = threading.Thread(target=timer)
runner_proc = multiprocessing.Process(target=runner)

runner_proc.start()

submit( Task(5, f, ("5 sec", )) )
submit( Task(1, f, ("1 sec", )) )
submit( Task(2, f, ("2 sec", )) )
import random
tasks = [Task(random.randint(1,5), f, (i,)) for i in range(1,1000)]
for t in tasks:
    submit(t)

timer_thread.start()
