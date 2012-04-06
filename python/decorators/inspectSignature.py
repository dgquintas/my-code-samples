import inspect

def getPrintableFunctionSignature(f):
  argSpec = inspect.getargspec(f)

  args = argSpec[0]
  if not args:
    args = (None, )
  defs = argSpec[3]
  if not defs:
    defs = (None, )

  argsWithDefs = reversed(map( lambda a,d: d and ( '%s=%s' % (a,d) ) or str(a), \
      reversed(args), reversed(defs) ) )

  return '(%s)' % (', '.join(argsWithDefs))


def signatureDecorator(name=None):
  def _(f):
    fname = name or f.__name__
    f.__doc__ = '%s%s: %s' % (fname, getPrintableFunctionSignature(f), f.__doc__ or '')
    return f
  return _ 

@signatureDecorator('cipote')
def f(a,b,c=123):
  """a docstring"""
  pass

print f.__doc__

