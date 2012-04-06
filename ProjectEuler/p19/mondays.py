def getDeviation(month, year):
  deviation = (1, 
    (-2,-1), 
    1,
    0,
    1,
    0,
    1,
    1,
    0,
    1,
    0,
    1)
  if month == 2:
    res = deviation[2][isLeap(year)]
  else:
    res = deviation[month]

  return res

def isLeap(year):
  if year % 100 == 0:
    return year % 400 == 0
  else:
    return year % 4

