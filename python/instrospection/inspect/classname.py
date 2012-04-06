import inspect
import pprint 

def getClassName():
  invokingFrame = inspect.getouterframes(inspect.currentframe())[1]
  nameInFrame = invokingFrame[3]
  return nameInFrame


class Foo(object):

  name = getClassName()
  
  def __init__(self):
    pass

  def f(self):
    pprint.pprint(self.name)


def g():
  name = getClassName()
  print "getClassName() from withing func g():", name

def callG():
  g()

foo = Foo()
foo.f()

print
callG()
