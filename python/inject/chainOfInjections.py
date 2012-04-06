import inject
@inject.appscope
class A(object):
 
  @inject.param('b')
  def __init__(self, b):
    self.b = b

  def __unicode__(self):
    return u"Soy A con b = %s" % self.b

  __str__ = __unicode__

class Base(object):
  @inject.param('a', A)
  def __init__(self, a):
    print "In Base: a = %s" % a




injector = inject.Injector()
inject.register(injector)

injector.bind('b', to='soy b')

#Base gets an instance of A that's automatically constructed. In turn,
#A's instance is constructed using the bound instance of 'b'
base = Base()

