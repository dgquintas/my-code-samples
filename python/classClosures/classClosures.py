#The methods of a nested class may access the instance attributes of the nested class instance but not of any outer class instance: http://www.brpreiss.com/books/opus7/html/page598.html

class A(object):

  def __init__(self):
    self.foo = 1
    self.aa = A.AA(self)

  def f(self):
    self.aa.ff()

  class AA(object):
    def __init__(self, outer):
      self._outer = outer 

    def ff(self):
      print self._outer.foo


a = A()
a.f()
