#ArgSpec(args=['self', 'foo', 'f00', 'bar'], varargs=None, keywords=None, defaults=(1, '123'))
def getPrintableFuncDescr(argSpec):
  args = argSpec.args
  defs = argSpec.defaults


  argsWithDefs = reversed(map( lambda a,d: d and ( '%s=%s' % (a,d) ) or str(a), \
    reversed(args), reversed(defs) ) )

  return ', '.join(argsWithDefs)

class C(object):
  def __init__(self):
    pass
  def a(self, foo, bar='123'):
    pass
  def b(self, kk):
    pass
  def _private(self):
    pass
  @staticmethod
  def staticmethod():
    pass

import inspect
from pprint import pprint

#it doesn't really matter whether we use the class itself, C, or
#an instance thereof
c = C()
print "all methods:"
allmethods = inspect.getmembers(c, inspect.ismethod)
pprint(allmethods)

print "\nonly 'public' methods"
#publicmethods = filter( lambda method: method[0][0] != '_', allmethods)
publicmethods = inspect.getmembers(c, lambda x: inspect.ismethod(x) and x.__name__[0] != '_')
pprint(publicmethods)

print "\nsignature of C's a method"
print inspect.getargspec(publicmethods[0][1])
print getPrintableFuncDescr(inspect.getargspec(publicmethods[0][1]))
