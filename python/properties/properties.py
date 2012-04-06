class C(object):
    def __init__(self):
        self._x = None

    @property
    def x(self):
        """I'm the 'x' property."""
        return self._x

    @x.setter
    def x(self, value):
        self._x = value

    @x.deleter
    def x(self):
        del self._x


c = C()
print c.x
c.x = 1
print c.x
c.x = 2
print c.x

class D(object):
    def __init__(self):
        self._x = "Can't set me"

    @property
    def x(self):
        """I'm the 'x' property."""
        return self._x


d = D()
print d.x
print D.x
d.x = "This will fail"
