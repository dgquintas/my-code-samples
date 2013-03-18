# if an argument is given both explicitly and in the **kwargs, which one
# takes precedence?

def f(foo=1, **kwargs):
    print(foo)

d = {'foo':2, 'bar':3}
f(**d) # => will print "2", **thus kwargs takes precedence**
