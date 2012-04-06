import pdb

def gen():
  x = 1 
  while True:
    x = (yield x+1)
    print "x is now", x

pdb.set_trace()
g = gen()
print "from next:", g.next()
print [g.send(i**2) for i in xrange(10)]
