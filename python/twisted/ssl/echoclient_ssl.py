from twisted.internet import ssl, reactor
from twisted.internet.protocol import ClientFactory, Protocol

class EchoClient(Protocol):
    def connectionMade(self):
        print "hello, world"
        self.transport.write("hello, world!")

    def dataReceived(self, data):
        print "Server said:", data
        self.transport.loseConnection()

class EchoClientFactory(ClientFactory):
    protocol = EchoClient

    def clientConnectionFailed(self, connector, reason):
        print "Connection failed - goodbye!"
        reactor.stop()

    def clientConnectionLost(self, connector, reason):
        print "Connection lost - goodbye!"
        reactor.stop()

if __name__ == '__main__':
    factory = EchoClientFactory()
    reactor.connectSSL('localhost', 8000, factory, ssl.ClientContextFactory())
    reactor.run()


