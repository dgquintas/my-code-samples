from math import sqrt
baseValue = ord('A')-1

def isTriangular(n):
 res = sqrt((n << 3)+1)
  resint = int(res)
  return ( res - resint == 0 )

def getNumericalValue(w):
  global baseValue
  return sum( ( (ord(l) - baseValue) for l in w) )

from itertools import ifilter 
f = file("words.txt", 'r')
words = f.readline()
print sum( ifilter(None, 
  (isTriangular(getNumericalValue(w[1:-1])) for w in words.split(',')) 
  )
)

