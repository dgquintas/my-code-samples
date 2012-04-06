""" 
http://docs.python.org/reference/datamodel.html 

Function objects also support getting and setting arbitrary
attributes, which can be used, for example, to attach
metadata to functions. Regular attribute dot-notation is
used to get and set such attributes. Note that the current
implementation only supports function attributes on
user-defined functions. Function attributes on built-in
functions may be supported in the future.
"""
def f():
  f.a = 1
  def g():
    print "upon entry in g; a =", f.a
    f.a = 2
    print "upon exit from g; a =", f.a
  g()
  print "after g(); a =", f.a
  return f.a

print f()


# now with a class
# we can't do it in the same way because:
# Methods also support accessing (but not setting) the arbitrary function
# attributes on the underlying function object.
class C(object):

  def f(self):
    def holder(): pass
    holder.a = 1
    def g():
      print "upon entry in g; a =", holder.a
      holder.a = 2
      print "upon exit from g; a =", holder.a
    g()
    print "after g(); a =", holder.a
    return holder.a

print C().f()


