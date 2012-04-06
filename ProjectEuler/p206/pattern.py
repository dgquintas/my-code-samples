import re
matcher = re.compile("1.2.3.4.5.6.7.8.9.0")

i = 1000000030

while i <= 1414213562:
  if matcher.match(str(i*i)):
    print i
    break
  if i % 100 == 30:
    i += 40
  else: # ...70
    i += 60

