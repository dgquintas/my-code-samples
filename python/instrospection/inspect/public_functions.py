import inspect, sys
from pprint import pprint

def a(self, foo, bar='123'):
  pass
def b(self, kk):
  pass
def _private(self):
  pass

mod = sys.modules[__name__]
print 'This file belongs to module', mod

print "all methods:"
allmethods = inspect.getmembers(mod, inspect.isfunction )
pprint(allmethods)

print "\nonly 'public' methods"
#publicmethods = filter( lambda method: method[0][0] != '_', allmethods)
publicmethods = inspect.getmembers(mod, \
        lambda x: inspect.isfunction(x) and x.__name__[0] != '_')
pprint(publicmethods)
