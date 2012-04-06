def funA():
  print "A"

def funB():
  print "B"

def funOther():
  print "Other"

fa = locals()['funA']
fa()
