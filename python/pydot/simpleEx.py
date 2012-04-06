import pydot

edges=[(1,2), (1,3), (1,4), (3,4), (1,1)]
g=pydot.graph_from_edges(edges)
g.set_type('digraph')
g.write_jpeg('graph_from_edges_dot.jpg', prog='dot') 
