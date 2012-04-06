from Crypto.Util import number
from math import log10, floor
import itertools

LIMIT = 1000

def getPrimes(start = 2L):
  if start <= 2:
    yield 2L
    start = 3L
  n = long(start)
  while True:
    if number.isPrime(n):
      yield n
    n += 2

def changeFirstDigit(n):
  d = n % 10
  n -= d
  return [ (n+i) for i in (1,3,7,9) if i != d]

def changeIthDigit(n, i):
  mask = (10 ** i)
  d = ( n / mask ) % 10
  d *= mask
  n -= d 
  return [ (n + (i*mask)) for i in range(0,10) if i != d]

def isListContainingNonPrimeProof(l):
  for j in l:
    if number.isPrime(long(j)):
      return True


def isPrimeProof(n):
  l = changeFirstDigit(n)
  if isListContainingNonPrimeProof(l):
    return False
    
  numDigits = int(floor(log10(n)+1))
  for i in range(1,numDigits):
    l = changeIthDigit(n,i)
    if isListContainingNonPrimeProof(l):
      return False
  return True



def getSqubes(limit):
  for p in range(limit/50):
    for q in range(p+1,limit*50):
      yield (primes[p]**2)*(primes[q]**3)
      yield (primes[q]**2)*(primes[p]**3)


if __name__ == "__main__":
  global primes
  primesGen = getPrimes()
  primes = tuple(itertools.islice(primesGen, LIMIT*50))
  squbesGen = getSqubes(LIMIT)
  l = filter(isPrimeProof, itertools.ifilter(lambda x: "200" in str(x), squbesGen) )
  l.sort()
  print l[190:210], len(l)
