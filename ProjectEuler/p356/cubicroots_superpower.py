from __future__ import print_function
from functools import partial

from mpmath import mp, mpf, findroot, nstr, log

def poly(x,n):
    power_of_2 = 1<<n
    x_mp = mpf(x)

    return x**3 - power_of_2 * x**2 + n

if __name__ == "__main__":
    
    f = poly
    mp.prec = 10000

    roots = [findroot( partial(f,n=n), float(2**n)) for n in range(1,30+1)]
    a_pelo = [ (1<<n) - n for n in range(1,30+1)]

    for i,r in enumerate(roots):
        print(i+1, nstr(r,50), a_pelo[i] )
    
