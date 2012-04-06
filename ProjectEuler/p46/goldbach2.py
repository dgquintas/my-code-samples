from Crypto.Util import number
from math import ceil, sqrt
from itertools import ifilterfalse, dropwhile, count, imap

def canbe_written( odd_composite):
   # odd_composite = prime + 2*square
   for double_square in (2*n*n for n in count(1)):
      prime = odd_composite - double_square
      if prime < 0: break # consider `1' as a prime too
      if number.isPrime( long(prime) ):
         return True     
   return False

if __name__ == "__main__":
  odd_composites = ifilterfalse( number.isPrime, imap(long, xrange( 9, 10**9, 2)))
  print dropwhile( canbe_written, odd_composites).next()



