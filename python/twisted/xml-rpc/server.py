from twisted.web import xmlrpc, server
from twisted.internet import reactor, defer
import time

class Example(xmlrpc.XMLRPC):
  """An example object to be published."""

  def xmlrpc_echo(self, x):
    """Return all passed args."""
    return x

  def xmlrpc_add(self, a, b):
    """Return sum of arguments."""
    return a + b

  #THIS PATTERN IS TEH AWESOME!!!11
  def xmlrpc_syncCall(self, x):
    def fail(_):
      print "faaaail"
      return False

    def success(result):
      return result

    d = defer.Deferred()
    reactor.callLater( 5, d.callback, x*3 )
    return d.addCallbacks(success, fail)



if __name__ == '__main__':
  from twisted.internet import reactor
  r = Example()
  reactor.listenTCP(7080, server.Site(r))
  reactor.run()
