import SocketServer, time
from SimpleXMLRPCServer import SimpleXMLRPCServer,SimpleXMLRPCRequestHandler

# Threaded mix-in
class AsyncXMLRPCServer(SocketServer.ForkingMixIn,SimpleXMLRPCServer): 
  def close_request(self, request): 
    SimpleXMLRPCServer.close_request(self,request)
    SocketServer.ForkingMixIn.collect_children(self)

# Example class to be published
class TestObject:

  def __init__(self):
    self.n = 0

  def pow(self, x, y):
    return pow(x, y)

  def iadd(self, x) :
    self.n = self.n + x
    return self.n

  def add(self, x, y) :
    return x + y

  def divide(self, x, y):
    return float(x) / float(y)


# Instantiate and bind to localhost:8080
server = AsyncXMLRPCServer(('', 8080), SimpleXMLRPCRequestHandler)

# Register example object instance
server.register_instance(TestObject())

# run!
server.serve_forever()
