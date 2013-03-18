class ClassProperty(property):
    def __get__(self, cls, owner):
        return self.fget.__get__(None, owner)()

class C(object):

    @ClassProperty
    @classmethod
    def f(cls):
        return cls.__class__.__name__

    @property
    def g(self):
        return self.__class__.__name__


print(C.f)
c = C()
print(c.f)
print(c.g)

