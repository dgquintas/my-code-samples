from SimpleHTTPServer import SimpleHTTPRequestHandler
from BaseHTTPServer import HTTPServer
import md5

class HTTPReqHandlerWithPUT(SimpleHTTPRequestHandler):
  def do_PUT(self):
    print self.command
    print self.path
    n = int(self.headers['Content-Length'])
    ctnt = self.rfile.read(n)
    print len(ctnt)
    print md5.new(ctnt).hexdigest()
    self.send_response(200)






def main():
  try:
    server = HTTPServer(('', 8080), HTTPReqHandlerWithPUT)
    server.serve_forever()
  except:
    server.socket.close()

if __name__ == '__main__':
  main()

