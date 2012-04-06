from random import randint

def gen6Trials():
  return [randint(1,6) for i in xrange(6)]

def gen9Trials():
  return [randint(1,4) for i in xrange(9)]


yes = 0
TIMES = 100000
for i in xrange(TIMES):
  c = gen6Trials()
  t = gen9Trials()

  if sum(c) < sum(t):
    yes += 1

print float(yes)/TIMES

#yes = 0
#TIMES = 200000
#for i in xrange(TIMES):
#  c = randint(1,6)
#  t = randint(1,4)
#  if (c-t) <= 2:
#    yes += 1
#
#print float(yes)/TIMES
  
    



