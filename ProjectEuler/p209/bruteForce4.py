def genInputs(n):
  if n == 1:
    yield [0]
    yield [1]
  else:
    for i in genInputs(n-1):
      yield [0] + i
      yield [1] + i

tts = [tt for tt in genInputs(16) ]

def isOk(tt, a,b,c,d):
  rowIdx1 = int("%d%d%d%d" % (a,b,c,d),2)
  rowIdx2 = int("%d%d%d%d" % (b,c,d, a ^ (b & c)),2)
  return (tt[rowIdx1] & tt[rowIdx2] == 0)
  
valids = 0
for tt in tts:
  for row in genInputs(4):
    if not isOk(tt, row[0], row[1], row[2], row[3]):
      break
  else:
    valids += 1

print valids
