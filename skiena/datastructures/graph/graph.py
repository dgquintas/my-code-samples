# based on skiena, p 153
#
# The idea is to use linked lists to store the neighbors adjacent to
# each vertex. Basically, we keep a "dictionary" (or list, if the label
# of the vertices doesn't matter) with the key the vertex and the value
# a list of an "edge" struct, such that in they contain the vertex
# at the other end plus a possible weight, or whatever. 

from collections import defaultdict

class Edge(object):
    def __init__(self, y, weight=None):
        self._y = y
        self._weight = weight

    @property
    def y(self):
        return self._y

    @property 
    def weight(self):
        if self._weight:
            return self._weight
        else:
            return 0

    def __eq__(self, other):
        return self._y == other._y and \
                self._weight == other._weight

    def __ne__(self, other):
        return not self.__eq__(self, other)

    def __hash__(self):
        return hash("%s/%s" % (self._y, self._weight))

    def __unicode__(self):
        out = ['%s' % self.y]
        if self.weight:
            out.append(' weight %d' % self.weight)
        return ''.join(out)

    def __str__(self):
        return unicode(self).encode('utf-8')

class Graph(object):
    def __init__(self, directed=False):
        self._verticesToEdgesMap = defaultdict(set)
        self._directed = directed

    @property
    def degree(self, vertex):
        if vertex not in self._verticesToEdgesMap:
            return 0
        edges = self._verticesToEdgesMap.get(vertex)
        return len(edges)

    @property
    def numVertices(self):
        return len(self._verticesToEdgesMap)

    @property
    def directed(self):
        return self._directed

    def addEdge(self, x, y, weight=None):
        e_y = Edge(y)
        self._verticesToEdgesMap[x].add(e_y)
        if not self.directed:
            e_x = Edge(x)
            self._verticesToEdgesMap[y].add(e_x)


    def __unicode__(self):
        out = []
        for v, edgs in self._verticesToEdgesMap.iteritems():
            out.append("Vertex %s:" % v)
            for e in edgs:
                out.append( "\t ==> %s" % e )
        return '\n'.join(out)

    def __str__(self):
        return unicode(self).encode('utf-8')



if __name__ == '__main__':
    g = Graph()

    g.addEdge(0,1)
    g.addEdge(0,2)
    g.addEdge(0,3)

    g.addEdge(1,2)
    g.addEdge(1,0)
    g.addEdge(1,3)

    g.addEdge(2,0)
    g.addEdge(2,1)
    
    g.addEdge(3,0)
    g.addEdge(3,1)

    print(g)
