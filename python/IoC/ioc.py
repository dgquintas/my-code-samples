#point is: can a base class depend on sth that gets
#injected to it by one of its children?

class Dependency(object):
  pass

class Base(object):
  def stuff(self):
    print self._dependency

class Deriv(Base):
  def __init__(self):
    self._dependency = Dependency()

d = Deriv()
d.stuff()

b = Base()
#this will fail
b.stuff()


