class Base(object):

  a = 1
  b = a
  print "@ Base"

  def __init__(self):
    pass


class Deriv(Base):

  a = 3
  print "@ Deriv"

  def __init__(self):
    pass

class Deriv2(Base):

  a = 4
  print "@ Deriv2"

  def __init__(self):
    pass


d = Deriv()
d2 = Deriv2()
print d.a, d.b
print d2.a, d2.b

#http://docs.python.org/reference/datamodel.html
#Class attribute assignments update the class’s dictionary, never the dictionary of a base class.


