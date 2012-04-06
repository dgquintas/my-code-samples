from __future__ import print_function
import sys
import collections
import threading
import os
import logging
import time
try:
    import queue
except ImportError:
    import Queue as queue

logging.basicConfig(level=logging.INFO, 
        format="%(asctime)s %(levelname)s [%(threadName)s] - %(message)s" )
logger = logging.getLogger()

g_mb_counters = collections.defaultdict(int) # MBs written by each thread
g_time_counters = dict() # time consumed by each thread


BUFSIZE = 1024*1024*10

class Barrier(object):
    def __init__(self):
        self.cond = threading.Condition(threading.Lock())
        self.q = queue.Queue()

    def wait(self):
        with self.cond:
            self.q.put(1)
            logger.debug("Waiting at barrier...")
            self.cond.wait()
            logger.debug("Yay crossed barrier!")
    
    def done(self):
        logger.debug("Thread done")
        self.q.put(0)

    def consume(self):
        return self.q.get()

    def release(self):
        logger.debug("Releasing all threads waiting at barrier")
        with self.cond:
            self.cond.notify_all()

class Writer(threading.Thread):
    def __init__(self, files, datasrc, barrier):
        threading.Thread.__init__(self)
        self.files = files
        self._datasrc = datasrc
        self._barrier = barrier
        logger.debug("Created thread %s for files %s", self.name, [f.name for f in files])

    def run(self):
        thread_start_time = time.time()
        while self._datasrc.data:
            for f in self.files:
                t = time.time()
                logger.debug("Starting to write to %s", f.name)
                f.write(self._datasrc.data)
                t = time.time() -t
                mb = len(self._datasrc.data)/1024**2
                logger.debug("Wrote %d MB to %s. Took %f secs (%f MB/s)", \
                        mb,f.name, t, mb/t)
                g_mb_counters[self.name] += mb

            # wait at the barrier for the rest of the threads
            self._barrier.wait()
        g_time_counters[self.name] = time.time() - thread_start_time
        self._barrier.done()

class DataHolder(object):
    def __init__(self, gen):
        self.data = next(gen)
        self._gen = gen

    def advance(self):
        try:
            logger.debug("Advancing...")
            self.data = next(self._gen)

        except StopIteration:
            self.data = None

def data_generator():
    while True:
        data = sys.stdin.read(BUFSIZE)
        if not data:
            break
        yield data

if __name__ == "__main__":
    if len(sys.argv) <= 1:
        print("Usage: %s FILE ..." % sys.argv[0], file=sys.stderr)
        sys.exit(1)

    start_time = time.time()
    outfiles = [ open(fn, 'w') for fn in sys.argv[1:] ]

    # group files by device
    files_by_dev = collections.defaultdict(list)
    for outfile in outfiles:
        dev = os.fstat(outfile.fileno()).st_dev
        files_by_dev[dev].append(outfile)
    
    dh = DataHolder(data_generator())
    # synch barrier
    b = Barrier()
    # create a thread for each entry in files_by_dev
    threads = [ Writer(files_by_dev[dev], dh, b) for dev in files_by_dev ]
    for t in threads:
        t.start()
 
    at_barrier = 0
    done = 0
    while True:
        logger.debug("Getting into barrier to see what's up")
        e = b.consume()
        logger.debug("Got '%r' from barrier's queue", e)
        if e == 0:
            done += 1
        else:
            at_barrier += 1
        if at_barrier == len(threads):
            dh.advance()
            at_barrier = 0
            logger.debug("About to release barrier")
            b.release() # wake up all waiting threads
        if done == len(threads):
            # all threads done and finished. 
            # This is an implicit join operation 
            break

    for outfile in outfiles:
        outfile.close()

    t = time.time() - start_time
    for tname in g_mb_counters:
        mb = g_mb_counters[tname]
        tt = g_time_counters[tname]
        mbps = g_mb_counters[tname] / g_time_counters[tname]
        logger.info("Thread %s wrote %f MB in %f secs (%f MB/s)", tname, mb, tt, mbps )

    s = sum( mbs for mbs in g_mb_counters.values() )
    logger.info("Total written: %f MB in %f secs (%f MB/s)" ,s,t,s/t)



