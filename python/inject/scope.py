import inject

@inject.appscope
class ASingleton(object):
 
  def __init__(self):
    pass

class Base(object):
  @inject.param('a')
  def __init__(self, a):
    print "In Base: a = %s" % a
    self.a = a

class Base2(object):
  @inject.param('aBis')
  def __init__(self, aBis):
    print "In Base: a = %s" % aBis
    self.a = aBis


injector = inject.Injector()
inject.register(injector)

injector.bind('a', to=ASingleton)
injector.bind('aBis', to=ASingleton)


base = Base()
base2 = Base()

assert base.a is base2.a


class ANoSingleton(object):
 
  def __init__(self):
    pass

injector.bind('a', to=ANoSingleton)

base = Base()
base2 = Base()

assert base.a is not base2.a

