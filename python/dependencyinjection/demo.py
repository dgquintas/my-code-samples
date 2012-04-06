from di import RequiredFeature, HasMethods, IsInstanceOf

######################################################################
## 
## DEMO
## 
######################################################################

# ---------------------------------------------------------------------------------
# Some python module defines a Bar component and states the dependencies
# We will assume that
# - Console denotes an object with a method WriteLine(string)
# - AppTitle denotes a string that represents the current application name
# - CurrentUser denotes a string that represents the current user name
#

class Bar(object):
   con   = RequiredFeature('Console', HasMethods('WriteLine'))
   title = RequiredFeature('AppTitle', IsInstanceOf(str))
   user  = RequiredFeature('CurrentUser', IsInstanceOf(str))
   foo = RequiredFeature('foo')
   def __init__(self):
      self.X = 0
   def PrintYourself(self):
      self.con.WriteLine('-- Bar instance --')
      self.con.WriteLine('Title: %s' % self.title)
      self.con.WriteLine('User: %s' % self.user)
      self.con.WriteLine('X: %d' % self.X)
      print self.foo


