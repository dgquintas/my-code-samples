class Base:
  def __init__(self, value):
    self.value = value

class Deriv(Base):
  def __init__(self, value):
    Base.__init__(self,value)


d = Deriv(33)

print d.value
print isinstance(d,Deriv)
print isinstance(d,Base)
