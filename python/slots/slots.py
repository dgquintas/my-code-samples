from __future__ import print_function
import sys

class MonitorNormal(object):
    def __init__(self, delta=0.0):
        self.delta = delta

    @property
    def name(self):
        return "MonitorNormal"

class MonitorSlots(object):
    __slots__ = ('delta',)

    def __init__(self, delta=0.0):
        self.delta = delta

    @property
    def name(self):
        return "MonitorSlots"

m1 = MonitorNormal(1.2)
m2 = MonitorSlots(1.2)


m1.foo = 'bar'
# m2.foo = 'bar' # will fail with AttributeError: 'MonitorSlots' object has no attribute 'foo'

print( m1.name, sys.getsizeof(m1) ) # 64
print( m2.name, sys.getsizeof(m2) ) # 56



