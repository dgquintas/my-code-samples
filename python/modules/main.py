import aModule

s = "x"
print aModule.__dict__[s]
print aModule.__dict__['f']

aModule.__dict__['a_new_one'] = 'profit!'
print aModule.a_new_one

import sys
thisModule = sys.modules[__name__]
print thisModule.__dict__["s"]
