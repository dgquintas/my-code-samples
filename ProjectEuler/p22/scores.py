def getValForName(name):
  res = 0
  base = ord("A")-1
  res = reduce( lambda x,c: x+ord(c)-base, name, 0)
  return res

f = file("names.txt")
s = f.read()
quotednames = s.split(',')
names = map(lambda x: x.strip()[1:-1], quotednames)
names.sort()
print reduce( lambda x,idx_name: x+(idx_name[0]+1)*getValForName(idx_name[1]), enumerate(names), 0)
#equiv:
#print sum(map( lambda idx_name: (idx_name[0]+1)*getValForName(idx_name[1]), enumerate(names)))
