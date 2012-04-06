def funA():
  print "A"

def funB():
  print "B"

def funOther():
  print "Other"


class FakeNamespace(object):
  @staticmethod
  def s():
    print "I'm a static method"

def main():
  n = raw_input("Input 'A' or 'B' if you don't want it to fail: " )
  try:
    f = eval( "fun" + n )
  except NameError:
    f = funOther
  f()

  ns = raw_input("Input 'FakeNamespace' now: ")
  c = eval( ns )
  c.s()



if __name__ == "__main__":
  main()

