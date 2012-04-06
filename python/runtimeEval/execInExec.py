class C(object):
  pass

class D(object):
  pass


def f(classToInstantiate):
  strToExec = "instance = %s()" % classToInstantiate
  exec strToExec in globals()

def g(classToInstantiate):
  innerStrToExec = "instance = %s()" % classToInstantiate
  strToExec = "exec '%s' in globals()" % innerStrToExec
  exec strToExec in globals()

for cls in ("C", "D"):
  f(cls)
  print type(instance)

del instance
for cls in ("C", "D"):
  g(cls)
  print type(instance)


