from random import randint
from collections import Counter

N = 5000000

f = lambda: randint(1, 200)

samples = [ max(f(), f()) for _ in range(N)]
c = Counter(samples)

hist = c.most_common()[::-1]
accum = []
s = 0
for h in hist:
    s += h[1]
    accum.append( (h[0], s) )
for h in accum:
    print("%d %d" % (h[0], h[1]))


