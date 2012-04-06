class Foo(object):

    perClass = 1

    def __init__(self):
        self.perClass += 1
        self.perInstance = 1

f = Foo()
print( "perClass, perInstance" )
print( f.perClass, f.perInstance )

ff = Foo()
print( "perClass, perInstance" )
print( ff.perClass, ff.perInstance )

# up to this point, this results in 
# perClass, perInstance
# 2 1
# perClass, perInstance
# 2 1
# 
# WTF right? The problem is that we are accessing the "static" attr
# perClass through an INSTANCE. For it to work statically, we ought to 
# do it through the class object

class Bar(object):

    perClass = 1

    def __init__(self):
        Bar.perClass += 1
        self.perInstance = 1

b1 = Bar()
print( "perClass, perInstance" )
print( b1.perClass, b1.perInstance )

b2 = Bar()
print( "perClass, perInstance" )
print( b2.perClass, b2.perInstance )
