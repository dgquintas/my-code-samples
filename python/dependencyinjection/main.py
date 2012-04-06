from di import features
from demo import Bar

# ---------------------------------------------------------------------------------
# Some third python module knows how to discover the current user's name
#
import os
def GetCurrentUser():
   return os.getenv('USER') or 'Some User' # USERNAME is platform-specific

# ---------------------------------------------------------------------------------
# Some other python module defines a basic Console component
#

class SimpleConsole(object):
   def WriteLine(self, s):
      print s

# ---------------------------------------------------------------------------------
# Yet another python module defines a better Console component
#

class BetterConsole(object):
   def __init__(self, prefix=''):
      self.prefix = prefix
   def WriteLine(self, s):
      lines = s.split('\n')
      for line in lines:
         if line:
            print self.prefix, line
         else:
            print



# ---------------------------------------------------------------------------------
# Finally, the main python script specifies the application name,
# decides which components/values to use for what feature,
# and creates an instance of Bar to work with
#
if __name__ == '__main__':
   print '\n*** IoC Demo ***'
   features.Provide('AppTitle', 'Inversion of Control ...\n\n... The Python Way')
   features.Provide('CurrentUser', GetCurrentUser)
   features.Provide('Console', BetterConsole, prefix='-->') # <-- transient lifestyle
   ##features.Provide('Console', BetterConsole(prefix='-->')) # <-- singleton lifestyle

   bar = Bar()
   bar.PrintYourself()



#
# Evidently, none of the used components needed to know about each other
# => Loose coupling goal achieved
# ---------------------------------------------------------------------------------
## end of http://code.activestate.com/recipes/413268/ }}}

