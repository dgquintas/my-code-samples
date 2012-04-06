from collections import namedtuple
from fractions import gcd
from math import sqrt, floor

# bound on m: from the fact that m^2+n^2 = k represent a circle with radius
# k. Thus both m and n < sqrt(k). 
# But that's a not very tight bound. A better one for n is derived from the 
# fact that Euclid's alg. for the generation of pythagorean triplets states that
# these are formed by (a,b,c) with a = m^2-n^2, b = 2mn, c = m^2+n^2 (from this
# last one springs the first bound).
# As we have to sum a+b+c, we have m^2-n^2 + 2mn + m^2 + n^2 = 2*(m^2)+2mn 
# which has to be < k. Solving for n, we have n < k/(2m) - m 

Triplet = namedtuple('Triplet','a,b c') 

def getPythTriplet(m,n):
  mSqr = m*m
  nSqr = n*n
  return Triplet(mSqr-nSqr, 2*m*n, mSqr+nSqr) 

r = 1.5e6
m_bound = int(floor(sqrt( r ))+1)
triplets = [getPythTriplet(m,n) \
        for m in range(2,m_bound,2) \
        for n in range(1,int(min(m, floor( r/(2*m) - m )+1)),2) if gcd(n,m) == 1] \
        + \
        [getPythTriplet(m,n) \
        for m in range(1,m_bound,2) \
        for n in range(2,int(min(m, floor( r/(2*m) - m )+1)),2) if gcd(n,m) == 1]


# the bound for k comes from the fact that k*s < r <=> k < r/s
multiples = {}
for t in triplets:
    #pdb.set_trace()
    s = sum(t)
    for k in range(1,int(floor(r/s)+1)):
        if multiples.has_key(k*s):
            multiples[k*s] += 1
        else:
            multiples[k*s] = 1
print( len(filter( lambda v: v == 1, multiples.values() )) )

