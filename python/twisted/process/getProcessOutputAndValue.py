from twisted.internet import utils, reactor

def foo():
  def p(res):
    print res[0]
  d = utils.getProcessOutputAndValue('whois', 'cern.ch')
  d.addCallback(p)
  d.addCallback(lambda _x: reactor.stop())


reactor.callWhenRunning(foo)
reactor.run()

