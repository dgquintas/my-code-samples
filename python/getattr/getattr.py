class C(object):

    def __init__(self):
        self.foo = 1

    def __getattr__(self, attr):
        if attr == "bar":
            return 2
        else:
            object.__getattribute__(self, attr)


c = C()
print(c.foo)
print(c.bar)
print(c.lol)

