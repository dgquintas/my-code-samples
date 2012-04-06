from pprint import pprint

def genCombinations(l,k):
  if k == 1:
    for e in l:
      yield [e]
  else:
    for i in xrange(len(l)):
      head = l[i]
      for j in genCombinations(l[i+1:],k-1):
        yield [head] + j 

print list(genCombinations([1,2,3,4,5],3))

##A = [1,3,6,8,10,11]
#A = map( lambda x:x*x, xrange(1,10+1) )
#k = 3
#g = genCombinations(A,k)
#combs = list(g)
#sumsset = set()
#for comb in combs:
#  s = sum(comb)
#  print comb, "->", s
#  if s in sumsset:
#    sumsset.discard(s)
#    print "discarded ", comb, " de suma ", s
#  else:
#    sumsset.add(s)
#print sum(sumsset)

