from Crypto.Util.number import isPrime #from pycrypt 
from math import sqrt, ceil

# we can approximate the n for the nth fibonacci number by
# taking into account that lim(F(n+1)/F(n), n->oo) = phi
# therefore, F(n+1) \approx phi*F(n). 
# in particular, F(n) \approx phi**(n-2)
# Taking the logarithm base phi, log(227000)/log(phi) = ~25.62
# which means the 26th Fibonacci number will be a good starting point.
# By virtue of Binet's formula, F(n) = (phi**n - (-1/phi)**n)/sqrt(5), we
# can quickly calculate the "starting points" for a Fibonacci generator

PHI = (1+sqrt(5))/2

def binet(n):
  PHI_n = PHI**n
  invPHI_n = 1/PHI_n
  if n & 0x1: #n is odd
    invPHI_n *= -1
  res = ( PHI_n - invPHI_n )/sqrt(5)
  return int(res)

def fibo(n0=0, n1=1):
  while True:
    res = n0 + n1
    n0, n1 = n1, res
    yield res

F26 = binet(26)
F27 = int(ceil(F26 * PHI))

fg = fibo(F26, F27)
while True:
  nf = fg.next()
  if isPrime(nf):
    print nf
    break


