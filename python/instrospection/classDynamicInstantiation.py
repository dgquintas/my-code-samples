# http://stackoverflow.com/questions/990422/how-to-get-a-reference-to-current-modules-attributes-in-python/990450#990450
class A(object):
    def __init__(self, **kwargs):
        self.kwargs = kwargs

    def hi(self):
        print("hello! I've been fed: ", self.kwargs)

def getClassFromThisModule(name):
    clazz = globals()[name]
    return clazz 

AClass = getClassFromThisModule('A')
a = AClass(uno=1, dos=2)
print(a)
a.hi()

