from __future__ import print_function
from multiprocessing import Pool
import time

def f(x):
    time.sleep(0.01)
    return x*x

def print_shit(shit):
    print(shit)

if __name__ == "__main__":
    pool = Pool() 
    for i in range(10000):
        pool.apply_async(f, (i,), callback=print_shit) #eval f(10) asynchronously

    print("all sent")
    pool.close()
    pool.join()

