from __future__ import print_function
class C(object):

  @classmethod
  def __init__(cls):
    cls.foo = 1

  @classmethod
  def printFoo(cls):
    print("cls.foo")

  @classmethod
  def factory(cls):
      return cls()

class D(C):
    
    @classmethod
    def printFoo(cls):
        print("HOLAAAAAAA")
        import platform
        if platform.python_version_tuple()[0] == 3:
            super().printFoo() #python3
        else:
            super(D, cls).printFoo() #python2
        print("ADIOSSSSS")

c = C()
c2 = C.factory()
print(c2.foo)
c.printFoo()
C.printFoo()
print()
d = D()
d.printFoo()
