class Base(object):

  def __init__(self):
    print "Base"


class DerivNoInit(Base):
  pass

class DerivInit(Base):

  def __init__(self):
    print "DerivInit"


dni = DerivNoInit()
di = DerivInit()

