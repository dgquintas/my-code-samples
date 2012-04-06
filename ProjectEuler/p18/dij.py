# Dijkstra's algorithm for shortest paths
# David Eppstein, UC Irvine, 4 April 2002

# http://aspn.activestate.com/ASPN/Cookbook/Python/Recipe/117228
from priodict import priorityDictionary

def Dijkstra(G,start,end=None):
	"""
	Find shortest paths from the start vertex to all
	vertices nearer than or equal to the end.

	The input graph G is assumed to have the following
	representation: A vertex can be any object that can
	be used as an index into a dictionary.  G is a
	dictionary, indexed by vertices.  For any vertex v,
	G[v] is itself a dictionary, indexed by the neighbors
	of v.  For any edge v->w, G[v][w] is the length of
	the edge.  This is related to the representation in
	<http://www.python.org/doc/essays/graphs.html>
	where Guido van Rossum suggests representing graphs
	as dictionaries mapping vertices to lists of neighbors,
	however dictionaries of edges have many advantages
	over lists: they can store extra information (here,
	the lengths), they support fast existence tests,
	and they allow easy modification of the graph by edge
	insertion and removal.  Such modifications are not
	needed here but are important in other graph algorithms.
	Since dictionaries obey iterator protocol, a graph
	represented as described here could be handed without
	modification to an algorithm using Guido's representation.

	Of course, G and G[v] need not be Python dict objects;
	they can be any other object that obeys dict protocol,
	for instance a wrapper in which vertices are URLs
	and a call to G[v] loads the web page and finds its links.
	
	The output is a pair (D,P) where D[v] is the distance
	from start to v and P[v] is the predecessor of v along
	the shortest path from s to v.
	
	Dijkstra's algorithm is only guaranteed to work correctly
	when all edge lengths are positive. This code does not
	verify this property for all edges (only the edges seen
 	before the end vertex is reached), but will correctly
	compute shortest paths even for some graphs with negative
	edges, and will raise an exception if it discovers that
	a negative edge has caused it to make a mistake.
	"""

	D = {}	# dictionary of final distances
	P = {}	# dictionary of predecessors
	Q = priorityDictionary()   # est.dist. of non-final vert.
	Q[start] = 0
	
	for v in Q:
		D[v] = Q[v]
		if v == end: break
		
		for w in G[v]:
			vwLength = D[v] + G[v][w]
			if w in D:
				if vwLength < D[w]:
					raise ValueError, "Dijkstra: found better path to already-final vertex"
			elif w not in Q or vwLength < Q[w]:
				Q[w] = vwLength
				P[w] = v
	
	return (D,P)
			
def shortestPath(G,start,end):
	"""
	Find a single shortest path from the given start vertex
	to the given end vertex.
	The input has the same conventions as Dijkstra().
	The output is a list of the vertices in order along
	the shortest path.
	"""

	D,P = Dijkstra(G,start,end)
	Path = []
	while 1:
		Path.append(end)
		if end == start: break
		end = P[end]
	Path.reverse()
	return Path


def triangToGraph(fName):
  f = file(fName)
  rows = f.readlines()
  G = {}
  r_i = len(rows)
  for row in rows[:0:-1]:
    r_i -= 1
    elems = row.split()
    for (e_i,e) in enumerate(elems):
      thisElemVertex = "%d_%d" % (r_i, e_i)
      leftParentVertex = "%d_%d" % (r_i-1, e_i-1)
      rightParentVertex = "%d_%d" % (r_i-1, e_i)
      toThisCost = 10000-int(e) 


      if 0 < e_i < r_i:
        if not G.has_key(leftParentVertex):
          G[leftParentVertex] = {}
        if not G.has_key(rightParentVertex):
          G[rightParentVertex] = {}

        G[leftParentVertex].update({thisElemVertex: toThisCost})
        G[rightParentVertex].update({thisElemVertex: toThisCost})
      elif e_i == 0: 
        if not G.has_key(rightParentVertex):
          G[rightParentVertex] = {}

        G[rightParentVertex].update({thisElemVertex: toThisCost})
      else: # e_i == r_i
        G[leftParentVertex].update({thisElemVertex: toThisCost})

  #"cauterize" the leafs of the graph
  leafs = rows[-1]
  for (e_i,e) in enumerate(leafs):
    thisElemVertex = "%d_%d" % (len(rows)-1, e_i)
    G[thisElemVertex] = {}

  return G

    

from pprint import pprint
if __name__ == "__main__":
  #pprint(triangToGraph('triang.txt'))
  G = triangToGraph('triangle.txt')
  #G = {'s':{'u':10, 'x':5}, 'u':{'v':1, 'x':2}, 'v':{'y':4}, 'x':{'u':3, 'v':9, 'y':2}, 'y':{'s':7, 'v':6}}
  res = Dijkstra(G, '0_0')[0] 
  res = [ res[k] for k in [ ("99_%d" % i) for i in range(100) ] ]
  m = min(res)
  print (99*10000 - m) + 59

