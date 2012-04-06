#see http://docs.python.org/reference/datamodel.html
#and http://docs.python.org/library/inspect.html#types-and-members

class C(object):
  def foo(self, a,b,c):
    """ ZOMG, A D0CSTRING!!11 """
    pass

codeObj = C.foo.func_code
print "%s -> %s\nDoc: %s" % \
  (codeObj.co_name, 
   codeObj.co_varnames[1:codeObj.co_argcount],
   C.foo.__doc__ )

