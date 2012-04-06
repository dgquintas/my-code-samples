#Used the Dice probability distribution (note the usage of caching to
#-dramatically- speed up the calculations given the nature of the F
#function) and then just combined the probabilities of the winning scenarios
#for the 4-sided dice. 
#http://en.wikipedia.org/wiki/Dice#Probability

cache = {}

def F(s,i,k):
  if cache.has_key((s,i,k)):
    return cache[(s,i,k)] 

  res = 0
  if i == 1:
    if 1 <= k <= s:
      res = 1.0/s
    else:
      res = 0
  else:
    for n in xrange(1,k+1):
      res += (F(s,1,n)*F(s,i-1,k-n))
  
  cache[(s,i,k)] = res
  return res

Cs = map( lambda k: F(6,6,k), xrange(36+1) )
Ts = map( lambda k: F(4,9,k), xrange(36+1) )

prob = 0.0
for i in xrange( len(Cs) ):
  for j in xrange(i+1, len(Ts) ):
    prob += (Cs[i] * Ts[j])

print "%.7f" % prob
