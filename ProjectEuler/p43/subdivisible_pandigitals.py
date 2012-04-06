from itertools import permutations

primes = (2,3,5,7,11,13,17)
def isSubstrDivisible(nStr):
    nStr = nStr[1:]
    for (i,p) in enumerate(primes):
        subint = int(nStr[i:i+3])
        if subint % p != 0:
            return False
    return True

res = []
for perm in permutations('0123456789'):
    n = ''.join(perm)
    if isSubstrDivisible(n):
        res.append(n)

print( sum( int(n) for n in res) )

