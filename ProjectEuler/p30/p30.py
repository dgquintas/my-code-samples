def isEqualToSumOfTheFifthPowerOfItsDigits(n):
  listOfDigits = map(lambda x: int(x) , str(n))
  res = sum( map(lambda x: x**5, listOfDigits) )
  return res == n

if __name__ == "__main__":
  l = filter( isEqualToSumOfTheFifthPowerOfItsDigits, xrange(2,int(10**6)) )
  print l
  print sum(l)
