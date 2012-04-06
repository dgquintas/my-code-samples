from math import floor, sqrt
from itertools import chain

N = 1000000
toIgnore = set()

def t(n):
  return 2*n*n-1

def sieve(n, p):
  global toIgnore
  if n in toIgnore: 
    return

  m = t(n)
  if m != p:
    toIgnore.add(n)

  while m % p == 0:
    m //= p
  if m > 1 and n+m < N:
    for mult in xrange(n+m, N+1, m):
      sieve(mult, m)
  if m-n >= 2 and m-n < N:
    for mult in xrange(m-n, N+1, m):
      sieve(mult, m)

for n in xrange(2, N+1):
  if n not in toIgnore:
    m = t(n)
    for mult in chain(xrange(n+m, N+1, m), xrange(-n+m, N+1, m)):
      sieve(mult, m)
print len(toIgnore)
    
    
