primes = [2, 3, 5, 7] # because if p | C(n,k), p <= n. (7**2 = 49)
primes = map( lambda x: x*x, primes)

from math import sqrt
def isSquareFree(n):
  for p2 in primes:
    if p2 > n:
      break
    if n % p2 == 0:
      return False
  return True

cache = {}
def binomial(n,k):
  if cache.has_key((n,k)) or cache.has_key((k,n)):
    return cache[(n,k)]
  res = 1
  if  0 < k < n:
    res = binomial(n-1,k-1) + binomial(n-1,k)

  cache[(n,k)] = res
  return res

coefs = set([1])
for r in xrange(1,51):
  coefs |= set( map( lambda k: binomial(r, k), xrange(1,(r/2)+1) ) )

print sum(filter(isSquareFree, coefs))

