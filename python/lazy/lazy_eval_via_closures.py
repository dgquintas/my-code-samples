# problem: we are implementing stuff at module-level (which means that
# lines get evaluated right away. We may run into a circular dependency
# upon initialization of something. 
# It'd be desirable to be able to postpone the initialization of the 
# "module attributes" until they are actually needed within the functions
# The idea is to use closures 

# Also, we don't want to re-create the object each
# time we need it. There's gotta be some kind of memoization

class C(object):
    def __init__(self):
        print("Constructing C")

# we DON'T want the following:
#
# c = C() 
#
# instead, we would like to DEFER C's construction until we really
# need to use "c".

print("Before defining lazy closure")
def c_factory():
    c = C()
    return lambda: c

def user_of_c():
    print("Before creating factory instance")
    get_c = c_factory()
    print("Before using 'c' within function")
    c = get_c()
    print("After using 'c' within function. 'c' is 0x%X" % id(c))
    c2 = get_c()
    print("And again... 'c2' is 0x%X" % id(c2))

user_of_c()




