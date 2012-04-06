from twisted.application import internet, service
from twisted.internet import protocol, defer
from twisted.protocols import basic

class FingerProtocol(basic.LineReceiver):
  def lineReceived(self, line):
    self.factory.getUser(line
      ).addErrback(lambda _: "Internal error in server"
      ).addCallback(lambda m: 
                    (self.transport.write(m + "\r\n"),
                     self.transport.loseConnection()))

class FingerFactory(protocol.ServerFactory):
  protocol = FingerProtocol
  def __init__(self, **kwargs):
    self.users = kwargs
  def getUser(self, user): 
    return defer.succeed(self.users.get(user, "No such user"))

application = service.Application('finger', uid=1, gid=1)
factory = FingerFactory(foo='bar')
internet.TCPServer(79, factory).setServiceParent(
    application)
