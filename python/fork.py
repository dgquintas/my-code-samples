import os

n = 123;

if os.fork() == 0:
  print "Child"
  print n - 100
else:
  print "Parent"
  print n + 100



