from Crypto.Util.number import isPrime
from math import sqrt
from itertools import takewhile,islice

def primesGen(ini=2L):
  if isPrime(ini):
    yield ini
  if not (ini & 0x1): #if even
    ini += 1 #make odd
  while True:
    if isPrime(ini):
      yield ini
    ini += 2
  
def factorsGenerator(n):
  primes = primesGen()
  lim = int(sqrt(n))+1
  for p in takewhile(lambda x: x <= lim, primes):
    power = 0
    while n % p == 0:
      power += 1
      n //= p
    if power > 0:
      yield (p, power)
    if isPrime(n):
      break
  yield (n,1)

def getPhisForRange(end):
  phis = range(end+1)
  lim =int(sqrt(end))+1
  pGen = primesGen()
  for p in islice( pGen , lim ):
    for i in xrange(p,end+1,p):
      phis[i] *= (1 - (1.0)/p)
  for p in takewhile( lambda x: x < end, pGen):
    phis[p] = p-1

  return [int(e) for e in phis[1:]]


def isPerm(a,b):
  a=[c for c in repr(a)]
  a.sort()
  b=[c for c in repr(b)]
  b.sort()
  return a == b

getPhisForRange(10000000)
#print [ (x[0]+1,x[1]) for x in enumerate(phis)]
