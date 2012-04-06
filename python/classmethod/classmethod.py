class C(object):

  @classmethod
  def __init__(cls):
    cls.foo = 1

  @classmethod
  def printFoo(cls):
    print cls.foo


c = C()
c.printFoo()
C.printFoo()
