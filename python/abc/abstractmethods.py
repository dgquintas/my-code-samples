import abc

class Base(metaclass=abc.ABCMeta):
    @abc.abstractmethod
    def abs_method(self):
        print("bar")

    def concrete(self):
        print("foo")

class Derived(Base):
    def abs_method(self):
        print("lol")

d = Derived()
