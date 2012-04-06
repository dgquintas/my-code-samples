def f_python3():
    v = False 
    def g():
        nonlocal v
        print("In g() before", v)
        v = True
        print("In g() after", v)

    print("before", v)
    g()
    print("after", v)

class Namespace: pass
def f_python2():
    ns = Namespace()
    ns.v = False
    def g():
        print("In g() before", ns.v)
        ns.v = True
        print("In g() after", ns.v)

    print("before", ns.v)
    g()
    print("after", ns.v)

import platform
if platform.python_version_tuple()[0] == '2':
    f_python2()
else:
    f_python3()

