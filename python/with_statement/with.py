from __future__ import with_statement

class ContextManager:

  def __enter__(self):
    print "entering"

  def __exit__(self, etyp, einst, etb):
    print "exiting"
    import traceback
    traceback.print_tb(etb)
    return True

def methodWithWith():
  with ContextManager():
    print "in the method"
    raise Exception("lol")

def main():
  methodWithWith()

if __name__ == '__main__':
  main()


