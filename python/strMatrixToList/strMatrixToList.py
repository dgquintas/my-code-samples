# "[ 1 2 ; 3 4 ] "

#str = raw_input()
str = "[ 1 2 ; 3 4 ] "

def toPy(str):
  res = []
  str = str.strip()
  str = str[1:-1].strip() #remove the external [ ]
  rows = str.split(';')
  for i in rows:
    res.append( i.split() )

  return res

def toStr(py):
  strRows = []
  map( lambda row: strRows.append(" ".join(row)), py)
  str = " ; ".join(strRows)
  str = "[ " + str +" ]"

  return str


py = toPy( str )
print py
str2 = toStr(py)
print str2
print toPy( str2 )
print toStr( toPy( str2 ) )
  




