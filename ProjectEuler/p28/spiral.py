from __future__ import division

def sumPerLevel(n): 
  return (n+1)**2 * (1+ n*(3/n - 6/((n+1)**2) ))

n = 1001
print 1+sum( (sumPerLevel(i) for i in xrange(2,n+1,2)))
