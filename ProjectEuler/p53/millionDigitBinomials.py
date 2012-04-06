import math

LOG10_2PI = math.log10(2*math.pi)
LOG10_E = math.log10( math.e )

def numDigitsFactorial(n):
  logn = math.log10(n)
  a = 0.5 * (LOG10_2PI + logn )
  b = n * ( logn - LOG10_E )
  return a+b

res = 0

for i in range(20, 100+1):
  for j in range(3,i):
    combDigits = numDigitsFactorial(i) - \
                 numDigitsFactorial(j) - \
                 numDigitsFactorial(i-j)
    if combDigits > 6:
      res += 1

print( res )


