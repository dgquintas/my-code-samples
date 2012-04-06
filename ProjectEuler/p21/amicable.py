from utils.multiplicative import forPrimesSigma_1, combinePrimePowerSigma_1, multiplicativeFunctionSieveGenerator


N = 25320 # max( sigma(a) -a ) forall a in [1..10000]= 9240 = 2**3 * 3 * 5* 7* 11
sigmas = list(multiplicativeFunctionSieveGenerator(N, forPrimesSigma_1, combinePrimePowerSigma_1))
sigmaNminusN = map( lambda x: x[1]-x[0], enumerate(sigmas) )
amicables = set()
for a, sigmaA in enumerate(sigmas):
  if a > 10000:
    break
  b = sigmaNminusN[a]
  if sigmas[b] == sigmaA and b != a:
    amicables.add(a)

print amicables
print sum(amicables)

