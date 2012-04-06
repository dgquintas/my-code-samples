#! /usr/bin/python

from twisted.internet import protocol
from twisted.internet import reactor
import re

class MyPP(protocol.ProcessProtocol):
    def __init__(self):
        self.data = ""
        self.err = ""
    def connectionMade(self):
        print "connectionMade!"
        self.transport.write("foobar")
        self.transport.closeStdin()

    def outReceived(self, data):
        print "outReceived! with %d bytes!" % len(data)
        self.data += data
    def errReceived(self, data):
        print "errReceived! with %d bytes!" % len(data)
        self.err += data

    def inConnectionLost(self):
        print "inConnectionLost! stdin is closed! (we probably did it)"
    def outConnectionLost(self):
        print "outConnectionLost! The child closed their stdout!"
        print self.data
    def errConnectionLost(self):
        print "errConnectionLost! The child closed their stderr."
        print self.err
        
    def processExited(self, reason):
        print "processExited, status %d" % (reason.value.exitCode,)
    def processEnded(self, reason):
        print "processEnded, status %d" % (reason.value.exitCode,)
        print "quitting"
        reactor.stop()

pp = MyPP()

def spawn():
  reactor.spawnProcess(pp, "nc", "nc localhost 1234".split(), env=None)

reactor.callWhenRunning(spawn)
reactor.run()

