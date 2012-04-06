NUM_LIMIT = 10000
ITER_LIMIT = 50

def isPalindrome(x):
  xStr = str(x)
  return xStr == xStr[::-1]

def isLychrel(x):
  for i in xrange(ITER_LIMIT):
    reversedXStr = str(x)[::-1]
    reversedX = int(reversedXStr)
    if isPalindrome( x + reversedX ):
      return False
    else:
      x += reversedX
  return True


if __name__ == "__main__":
  lyrichrelNums = []
  for i in xrange(NUM_LIMIT):
    if isLychrel(i):
      lyrichrelNums.append(i)
  print lyrichrelNums, len(lyrichrelNums)
  print filter( isPalindrome, lyrichrelNums)

