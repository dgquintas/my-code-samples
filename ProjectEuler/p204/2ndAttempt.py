from math import log, ceil,exp, floor

log2 = log(2)
log3 = log(3)
log5 = log(5)

hamNumbers = []

lim = log( 10**9 )

lim2 = int(floor( lim/log2 ) ) + 1
lim3 = int(floor( lim/log3 ) ) + 1
lim5 = int(floor( lim/log5 ) ) + 1

for e1 in xrange(lim2):
  for e2 in xrange(lim3):
    for e3 in xrange(lim5):
      res = e1*log2 + e2*log3 + e3*log5
      if res <= lim:
        hamNumbers.append(int(round(exp(res))))

print len(hamNumbers)


