from math import sqrt, floor 


LIM = 10**9

hammings = [] 

PRIMESLIM = int( floor( sqrt(LIM) ) ) 

primes = [True] * PRIMESLIM
primes[0] = primes[1] = False
def pregenPrimes():
  global primes
  for i in xrange(2,int(floor(sqrt(PRIMESLIM)))):
    if primes[i] == True:
      for m in xrange(i*i, PRIMESLIM, i):
        primes[m] = False
  primes = map(lambda x: x[0], filter(lambda x: x[1], enumerate(primes)))
   
def isHamming(n, degree):
  if n % 100000 == 0:
    print n / float(10**8)
  if n == 1:
    return True
  for p in primes:
    if p > degree:
      break
    while (p <= degree) and (n % p == 0): 
      n /= p
      if n <= degree:
        return True
  return False



TAONDE = 10**6

if __name__ == "__main__":
  pregenPrimes()
  res = filter( lambda x: isHamming(x, 5), xrange(1,TAONDE+1) )
  print len(res)

  #res = 
  #print len(res)


