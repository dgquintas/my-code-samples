import itertools
from Crypto.Util import number

#nothing particularly smart going on here, other than just
#generating all the numbers will the following digits:

# can start with it but cant have it in their "bodies": 2,5
# can ocurr in any part of the number: 1,3,7,9

#PS: this code SUUUUUUUUUUUUCKS. implement a PROPER ad-hoc method
#for combining the allowed digits in the given positions
front_digits = (2,5)
digits = (1,3,7,9)

def list_to_int(l):
    return int(''.join(map( str, l ) ))

def left_to_right(n, length):
    return ( n % (10**i) for i in range(1,length+1) )

def right_to_left(n, length):
    return ( n // (10**i) for i in range(length) )

res = 0
found = 0
i = 1
while i and found < 11: 
    combs = itertools.combinations_with_replacement(digits, i)
    for comb in combs:
        perms = []
        s = set( itertools.permutations( comb ) )
        perms.extend(s)
        for unique_comb in s:
            for fd in front_digits:
                t = [fd]
                t.extend( unique_comb )
                perms.append( t )
        prime_perms = filter( number.isPrime, ( list_to_int(perm) for perm in perms ) )
        for prime_perm in prime_perms:
            ltr = [ number.isPrime(p) for p in left_to_right(prime_perm, i) ]
            rtl = [ number.isPrime(p) for p in right_to_left(prime_perm, i) ]
            if all(ltr) and all(rtl) and prime_perm > 10:
                print(prime_perm)
                res += prime_perm
                found += 1
    i += 1
print(res)
