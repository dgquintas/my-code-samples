class MetaClass(type):
  @staticmethod
  def say_hello(self): print 'hello'
  def __new__(meta, classname, bases, classDict):
    print 'class name', classname
    print 'bases', bases
    classDict['say_blabla'] = MetaClass.say_hello
    print 'attrs', classDict
    return type.__new__(meta, classname, bases, classDict)

class Test:
#__metaclass__ can be set to any callable that accepts the same
#input as the 3-ary version of type()
  __metaclass__ = MetaClass

  def __init__(self):
    pass

  def method(self):
    pass

  classAttribute = 'sth'

#despite not inheriting (aparently) from 'object', at least according 
#to the src alone, we do in fact, because the class Bar is being constructed
#by Printable, which is to say that's being created by the 3-ary type()
print issubclass(Test, object)

t = Test()
t.say_blabla()
   
