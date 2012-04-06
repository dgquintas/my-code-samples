from utils.multiplicative import forPrimesSigma_1, combinePrimePowerSigma_1, multiplicativeFunctionSieveGenerator
from itertools import imap

N = 28123
g = multiplicativeFunctionSieveGenerator(N, forPrimesSigma_1, combinePrimePowerSigma_1)
sumProperDivs = imap( lambda (i,s): s-i, enumerate(g))
abundant_idx = filter(lambda (i,s): s > i, enumerate(sumProperDivs))
abundant = map( lambda x: x[0],abundant_idx)
pilaNumbers = set(xrange(1,N))
for i,n in enumerate(abundant):
  for m in abundant[i:]:
    pilaNumbers.discard(n+m)

print sum(pilaNumbers)
