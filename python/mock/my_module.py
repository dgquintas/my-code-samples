class Foo(object):
    def __init__(self, a):
        self._a = a

    def return_string(self):
        return "blah blah"

    @property
    def a(self):
        return self._a
