from __future__ import print_function
#from multiprocessing.dummy import Pool #to use threads instead of processes
from multiprocessing import Pool

import time

def f(x):
    return x*x

if __name__ == "__main__":
    pool = Pool(processes=4) # start 4 worker processes
    result = pool.apply_async(f, (10,)) #eval f(10) asynchronously
    print( result.get() )


    print( pool.map(f, range(10)) )

    it = pool.imap(f, range(10) )
    print( it.next() )
    print( it.next() )
    print( it.next(timeout=1) )
