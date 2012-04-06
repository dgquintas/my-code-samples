LIMIT = 10**6

isprime = [True]*3163
A = [0] * (LIMIT+1)
A[1] = 1

for p in xrange(2,3163):
  if isprime[p]:
    # flag multiples of p as non-primes
    # this is a classic sieve
    for n in xrange(p*p,3163,p):
      isprime[n] = False 

    #for each multiple of the prime p, temporally 
    #store p -the smallest divisor- in the sigma's list 
    for n in xrange(p*p,LIMIT+1,p):
      A[n] = p

for n in xrange(2,LIMIT+1):
  if A[n] == 0: # n prime
    A[n] = 2
  else:
    p = A[n]
    k = n / p
    e = 2 
    while k % p == 0:
      k /= p
      e += 1
    A[n] = A[k] * e


from itertools import *

ss = sum(ifilter(None, imap( lambda x,y: x == y, A, A[1:-1] )))
print ss

#s = 0
#for i in xrange(len(A)-1):
#  if A[i] == A[i+1]:
#    s += 1
#print s
#
#assert s == ss




#def main():
#  for n in xrange(2,LIMIT+1):
#    getSigmaZero(n)
#    if n % 100000== 0:
#      print (n / float(LIMIT))*100
#  print len(cache)
#
#
#if __name__ == "__main__":
#  main()
#

