from Crypto.Util import number
from math import ceil, sqrt
import itertools

def getPrimes(start = 2L):
  if start <= 2:
    yield 2L
    start = 3L
  n = long(start)
  while True:
    if number.isPrime(n):
      yield n
    n += 2

def upperLimitOnS(n,p):
  return int(ceil( sqrt( (n-p)/2 ) ))

if __name__ == "__main__": 
  try:
    for n in ( i for i in xrange(33L, 100001, 2) if not number.isPrime(long(i))): 
      two = itertools.dropwhile(lambda x: x != n, 
        ( p + 2*(s*s) for p in itertools.takewhile(lambda pr: pr < n, getPrimes(3))  
            for s in range(1, upperLimitOnS(n, p)+1) ) )

      two.next()
  except:
     print "faaail for", n

