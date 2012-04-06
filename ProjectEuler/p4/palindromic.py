def isPalindrome(x):
  txtualRepr = str(x)
  k = len( txtualRepr )
  halfK = k >> 1
  for i in range(halfK):
    if txtualRepr[i] != txtualRepr[-(i+1)]:
      return False
  return True

def checkFor6DigitPalFromTwo3DigitFactors():
  pals = []
  for a in xrange(999,1,-1):
    for b in xrange(999,1,-1):
      candidate = a * b
      if isPalindrome( candidate ):
#        print candidate, "=", a, "*", b
        pals.append((candidate,a,b))
  return pals

if __name__ == '__main__':
# print isPalindrome(input())
  pals = checkFor6DigitPalFromTwo3DigitFactors()
  print max(pals)


