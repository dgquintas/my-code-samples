from pprint import pprint

def genInputs(n):
  if n == 1:
    yield [0]
    yield [1]
  else:
    for i in genInputs(n-1):
      yield [0] + i
      yield [1] + i

from random import randint
def t(a,b,c,d):
#  if v:
#    nextV = False
#  else:
##    nextV = bool(randint(0,1)) 
#    nextV = True
  if graph.has_key((a,b,c,d)) : #cycle
    next= g.next()
    apply(t, next )
  else: #new entry point
    child = (b,c,d, a ^ (b & c))
    graph[(a,b,c,d)] = child 
    if len(graph) < 16:
      apply(t, child )


#def applyTT(tt, input):
#  for row in tt:
#    if row[0] == input:
#      return row[1]
#
#def checkTT():
#  tt = zip(seq, vals)
##  pprint(tt)
#  g = genInputs(6)
#  for row in g:
#    a,b,c,d,e,f = row[0], row[1], row[2], row[3], row[4], row[5]
#    if applyTT(tt,(a,b,c,d,e,f)) & applyTT(tt, (b,c,d,e,f, a ^ (b & c) )):
#      print row, (b,c,d,e,f, a ^ (b & c) )
#  print "checked"


graph = {}
g = genInputs(4)
apply(t,g.next()) 
pprint(graph)

import pydot
edges = map( lambda x: (x, graph[x]), graph )
g = pydot.graph_from_edges(edges)
g.set_type('digraph')
g.write_jpeg('mierda.jpg', prog='dot') 






