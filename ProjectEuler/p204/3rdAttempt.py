from math import log, ceil,exp, floor
primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
    67, 71, 73, 79, 83, 89, 97, 101]

logs = [1.0,1.0] + map( log, xrange(2,101) )

hamNumbers = []

lim = 10**9

degree = 100
 
loglim = log( lim )

lims = map( lambda x: int( floor( loglim/x ) ) + 1, logs )

def getNextPrime(n):
  return primes[primes.index(n)+1]

def combine(prev, p):
  if p > degree:
    hamNumbers.append(int(round(exp(prev))))
  else:
    for e in xrange(lims[p]):
      next = prev + e * logs[p]
      if next <= loglim:
        combine(next, getNextPrime(p))
      else:
        break
  return

combine(0,2)
print len(hamNumbers)

