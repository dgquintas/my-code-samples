from twisted.web.client import getPage
from twisted.internet import reactor

def lowerCaseContents(contents):
  return contents.lower()

def printContents(contents):
  print "deferred invocado printContents con el siguiente cont:"
  print contents

  #stop twisted's event handling system
  #this is usually handled in higher level ways
  reactor.stop()

print "before getPage"
deferred = getPage('http://www.google.com')
print "after getPage"

#the return value of the 1st callback is fed to the
#second callback func
deferred.addCallback(lowerCaseContents)
deferred.addCallback(printContents)

#this is usually handled in higher level ways
reactor.run()
