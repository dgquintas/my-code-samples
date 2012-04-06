class C(object):
    def __init__(self, x):
        self._x = x

    @property
    def x(self):
        return self._x

    @classmethod
    def factory(cls):
        inst = object.__new__(cls)
        inst._x = 1
        return inst

c = C.factory()
print(c.x) 
cc = C(2)
print(cc.x) 
