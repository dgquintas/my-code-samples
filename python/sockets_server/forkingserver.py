from SocketServer import TCPServer, ForkingMixIn, StreamRequestHandler

class Server(ForkingMixIn, TCPServer) : pass

class Handler(StreamRequestHandler):
  def handle(self):
    addr = self.request.getpeername()
    print 'Got connection from', addr
    self.wfile.write('Thanks for connecting\n')
    while True:
      raw = self.rfile.readline()
      if not raw:
        break
      readStr = str(raw)
      readStr = readStr[:-2]
      toRet = eval(readStr);
      self.wfile.write(str(toRet) + '\n' );

    

server = Server(('', 1234), Handler)
server.serve_forever()

