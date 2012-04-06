# - calculate the cubes of a bunch of numbers
# - count the number of each of their digits
# - match up counts: look for repeated values in the count dict

from itertools import count

def countDigits(n):
    s = str(n)
    return int(''.join([ str(s.count(str(i))) for i in range(0,10) ]))

cubes = ( i**3 for i in range(343, 10000) )
d = dict( (n, countDigits(n)) for n in cubes )

dd = dict()
ks = []
for (k,v) in sorted(d.items(),reverse=True):
    c = dd.setdefault(v,0)
    if c == 4: #the cube itself already counts as 1
        ks.append(k)
    else:
        dd[v] += 1

print(min(ks))

