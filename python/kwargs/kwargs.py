def f(x, **kwargs):
  print "x =", x
  print "kwargs = ", kwargs

def g(x, *args):
    print type(args)
    print "args = ", args

def h(foo, bar):
    print "foo = ", foo
    print "bar = ", bar

d = {"foo": "bar", "one": 1}
l = ("uno", "dos", "tres")

f("equis", **d)
print
f("equis 2", uno=1, dos=2)
f("equis 3", **{})

print "\n\n"
g('equis', 'one', 'two')
g('equis', 'eins', *l)
# g('equis', *l, 'am ende') doesnt work: only named arguments may follow *expression
g('equis', l) #this is WRONG (or usually not what's expected: it creates
              #a tuple with a single element inside (l), as opposed to
              #passing as many parameters as elements in l

print "\n\n"
dd = {'foo': 'yeeep', 'bar': 'also here'}
h(**dd)
