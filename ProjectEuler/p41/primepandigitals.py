# idea: the max n for an n-digit pandigital number is 9. 
# 9! is thus the max (without taking possible optimizations
# such as discarding perms with their last digit 5 or an even number).
# in addition, observe:
# 1) a number is divisible by 3 if the sum of its digits is div by 3
#    Thus 3-digit numbers (digits 1,2,3) will never be prime in this prob, as
#    1+2+3 = 6
# 2) Idem para n=2 (1+2 = 3)
# 3) Idem para n=5 (1+2+3+4+5 = 15)
# 4) Idem para n=6 (1+2+3+4+5+6 = 21)
# 5) Idem para n=8 (1+2+3+4+5+6+7+8 = 36)
# 6) Idem para n=9 (1+2+3+4+5+6+7+8+9=45)
#
# thus it can only be 4-digit or 7-digit


from Crypto.Util.number import isPrime
from itertools import permutations

def gen(n):
    digits = ''.join([str(i) for i in range(1,n+1)])
    pif = lambda p: int("".join(p))
    return ( pi for pi in 
            ( pif(p) for p in permutations(digits,n) )
            if isPrime(pi) )

for n in (4,7):
    print(n, max( gen(n) ))
