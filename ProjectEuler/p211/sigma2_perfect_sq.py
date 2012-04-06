import math

def sieve(up_to):
    ps = [2]
    i = 3
    while i < up_to:
        for p in ps:
            if i % p == 0:
                break
        else:
            ps.append(i)
        i += 2
    return ps

def sigmaprime(x, p, a):
    global primepowersigmas
    pps = primepowersigmas.setdefault(p, dict())
    if a not in pps:
        pps[a] = sum( p**(x*j) for j in range(0,a+1))
    return pps[a]


def sigma(x, n):
    if n == 1:
        return 1
    else:
        original_n = n 
        #extract all power of smallest prime factor
        for p in primes:
            a = 0
            while n % p == 0:
                n /= p
                a += 1
            if a > 0:
                #check if n / p^a has already been calculated
                if n not in sigmas:
                    sigmas[n] = sigma(x,n)

                res = sigmas[n] * sigmaprime(x, p, a) 
                if original_n < 8000:
                    sigmas[original_n] = res
                return res

        else:
            # n must be prime itself
            return sigmaprime(x,n,1)
                
def issquare(n):
    if (n & 7 == 1) or (n & 31 == 4) or (n & 127 == 16) or (n & 191 == 0):
        root = int(math.sqrt(n))
        return (root*root == n)
    else:
        return False



N = 64000000
x = 2 #for the sigma
largest_prime_factor = int(math.ceil(math.sqrt(N)))
primes = sieve(largest_prime_factor)

#initialize table for primes 
primepowersigmas = dict( (p, dict() ) for p in primes )
sigmas = dict( (p, sigmaprime(x,p,1) ) for p in primes )

res = 0
for i in range(1,N):
    s = sigma(x,i)
    if i % 1000000 == 0:
        print(i)
    if issquare(s):
        #print(i, " -> ", s)
        res += i

print( res )
