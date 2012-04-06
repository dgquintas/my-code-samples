class A(Exception):
  pass

try:
  a = A("msgggg")
  raise a
except Exception as e:
  print e
