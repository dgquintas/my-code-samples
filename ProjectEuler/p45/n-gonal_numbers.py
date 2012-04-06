from math import sqrt
from itertools import count

# Given that Pn = n(3n-1)/2, solving for n, we find that a pentagonal 
#verifies that 24n+1 is a perfect square (note that this is a necessary but
#NOT sufficient condition for "pentagonality"). 
# In particular, (6n-1)^2 == 1+24Pn

# every hexagonal number is also a triangular number. In fact, every other 
# triangular number is an hexagonal number (ie, Tn for odd n's). No need to
# check for triangularity if we are driven by hexagonal numbers

# it only remains to check that a given hexagonal number is also a pentagonal,
# in which case it'll be the three things. 

def isPerfectSqr(n):
  root = sqrt(n) 
  fractional = root % 1
  delta = 0.0001
  return fractional < delta
  
def isPentagonal(n):
  # if it turns out that the candidate is a perfect square, it MAY be a 
  # pentagonal number. 
  # the definite test is whether the solution to the pentagonal equation
  # 3n^2-n-2Pn==0 can be satisfied. That solves to n == (1+sqrt(1+24Pn))/6
  # That is, 1+sqrt(1+24Pn) gotta be a multiple of 6 for n to be an integer,
  # in which case it'll be the "index" of a pentagonal number (namely, Pn, 
  # of course)
  candidate = 1 + 24*n
  return isPerfectSqr(candidate) and (((int(sqrt(candidate))+1) % 6) == 0)

def hexagonalNumbers(i):
  return ( n*(2*n-1) for n in count(i) )

solution_generator = ( h for h in hexagonalNumbers(144) if isPentagonal(h) )

print( next(solution_generator) )

