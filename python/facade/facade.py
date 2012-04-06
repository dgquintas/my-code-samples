class C(object):
  def a(self): print "a"
  def b(self): print "b"

  def withArgs(self, arg1, arg2):
    print arg1, arg2


class Facade(object):

  def __init__(self, w):
    self._w = w
  
  def _wrap(self, f):
    print "pre %s" % f.__name__
    return f



  def __getattr__(self, attr):
    facadedMethod = getattr(self._w, attr)
    return self._wrap(facadedMethod)

f = Facade( C() )
f.a()
f.b()
f.withArgs("foo", "bar")
