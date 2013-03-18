# implement an LRU cache
# idea: 
# have a dictionary hash(key)->(index, associated-data) where the key is the value to 
# keep in the cache. 
# In addition, keep a (min)heap. Min = LRU. Values ~ (timestamp-last-occurrence, hash(key))

from __future__ import division

import heapq
import hashlib
import time
import collections
import array

import logging
logging.basicConfig(level=logging.INFO)

logger = logging.getLogger()

class LRU(object):

    _DELETED_HEAP_ITEM = object()

    _Entry = collections.namedtuple('Entry', 'ts, key, value')

    def __init__(self, maxsize):
        self.maxsize = maxsize

        self._d = {}
        self._h = []

    def __len__(self):
        return len(self._d)

    @staticmethod
    def _hash(key):
        return key
        #return int(hashlib.md5(key).hexdigest()[:8],16)
        #return hashlib.md5(key).hexdigest()

    def add(self, k, v):
        hkey = self._hash(k)

        if hkey in self._d:
            # update heap: size doesn't change
            # 1. recover the reference to the entry. Dictionary isn't changed 
            entry = self._d[hkey]

            # XXX: to be removed. This asumes the value is the
            # original key before hashing. just checking for collisions
            if entry.value != k:
                logger.warn("COLLISION: '%s'/'%s': %s", entry.value, k, hkey)

            # 2. update entry: create new based on old one
            updated = entry._replace(ts=time.time())

            logger.debug("Replacing '%s' with '%s' after the former "
                    "hadn't been used for %f secs",
                    entry, updated, time.time()-entry.ts)

            # 3. insert new one in heap
            heapq.heappush(self._h, updated)

            # 4. mark old one as deleted
            # this updates the entry in the heap too, being a shared 
            # reference to a mutable (list)
            entry = self._DELETED_HEAP_ITEM
        else: # first instance 
            new_entry = self._Entry(time.time(), hkey, v) 
            if len(self._d) < self.maxsize:
                self._d[hkey] = new_entry
                heapq.heappush(self._h, new_entry)
            else: # full
                # clean up items previously marked as deleted
                while self._h[0] is self._DELETED_HEAP_ITEM:
                    heapq.heappop(self._h)
                if self._h:
                    # delete LRU and insert new one
                    old_entry = heapq.heapreplace(self._h, new_entry)
                    del self._d[old_entry.key]
                else:
                    heapq.heappush(self._h, new_entry)

    def check(self, k):
        return k in self._d


if __name__ == "__main__":
    import random, os, base64, resource
    #from pympler.asizeof import asizeof

    words = ( base64.urlsafe_b64encode(os.urandom(100)) 
            for _ in range(200000) )

    lru = LRU(1000000)
    t = time.time()
    for w in words:
        #time.sleep(random.random()/100)
        lru.add(w, (w, len(w), time.time()))
    print time.time() - t, " secs"
    print len(lru)
    #print asizeof(lru)/(1024*1024)
    print resource.getrusage(resource.RUSAGE_SELF).ru_maxrss / 1024**2



    




