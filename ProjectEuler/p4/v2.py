#the palindrome will have the form
# abccba 
# therefore: abccba = 100000a + 10000b + 1000c +
#                   + 100c + 10b + a 
#                   = 100001a + 10010b + 1100c
#                   = 11(9091a + 910b + 100c)

def find6DigitPalindrome():
  x = 990
  y = 999
  for a in range(9,0,-1):
    for b in range(9,0,-1):
      for c in range(9,0,-1):






if __name__ == '__main__':
# print isPalindrome(input())
  pals = checkFor6DigitPalFromTwo3DigitFactors()
  print max(pals)


