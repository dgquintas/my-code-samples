def primeSieve(N):
  from math import sqrt,floor
  A = [0]*(N+1)
  limit =int(floor(sqrt(N))+1)
  isprime = [True]*limit

  for d in xrange(2,limit):
    if isprime[d]:
      for n in xrange(d*d, limit, d):
        isprime[n] = False
      for n in xrange(d*d, N+1, d):
        A[n] = d # d is n's smallest divisor
  return A

def multiplicativeFunctionSieveGenerator(N, forPrimes, combinePrimePower):
  A = primeSieve(N)
  yield 0 #A[0]
  A[1] = 1
  yield 1 
  for n in xrange(2,N+1):
    if A[n] == 0: #n prime
      A[n] = forPrimes(n)
    else: #n composite
      p = A[n] #p is n's smallest divisor
      k = n // p
      e = 1
      while k % p == 0:
        k //= p
        e += 1
      
      # n = k * (p**e), gcd(k,p) == 1
      if k == 1:
        A[n] = combinePrimePower(A,n,k,p,e)
      else:
        A[n] = A[k] * A[n // k]
    yield A[n]

def forPrimesSigma_1(n):
  return n+1
def combinePrimePowerSigma_1(A,n,k,p,e):
  j = n // k
  return A[ j // p] + j 

def forPrimesEulerPhi(n):
  return n-1
def combinePrimePowerEulerPhi(A,n,k,p,e):
  j = n // k #p**e
  j //= p # j = p**(e-1)
  return (p-1)*j

if __name__ == "__main__":
  N = 30
  print "euler phi's for 1..30"
  g = multiplicativeFunctionSieveGenerator(N, forPrimesEulerPhi, combinePrimePowerEulerPhi) 
  print list(enumerate(g))
  print "sigma_1's for 1..30"
  g = multiplicativeFunctionSieveGenerator(N, forPrimesSigma_1, combinePrimePowerSigma_1) 
  print list(enumerate(g))








