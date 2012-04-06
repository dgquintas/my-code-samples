def check_bin_palindrome(b):
  i=0
  while i < len(b)//2:
    if b[i] != b[-i-1]:
      return False
    i+=1
  return True


def f(n):
  res = []
  dd = (n-1)//2 +1
  dr = n//2

  first=1
  last=10**dd
  str_format = '%%0%dd' % dd
  for i in range(1, last, 2):
    if n > 1:
      i_str = str_format % i
      md = int(i_str[-dr:][::-1])
      md *= 10**dd
      md += i
    else:
      md = i
    binstr = bin(md)[2:]
    if check_bin_palindrome( binstr ):
      res.append( (md, binstr) )
  return res

from pprint import pprint
res = map( f, range(1,6+1) )
#pprint(res)
s = 0
for rr in res:
  for r in rr:
    s += r[0]

print s

#for i in xrange(1,1000000,2):
# if check_bin_palindrome( bin(i)[2:] ) and check_bin_palindrome( str(i) ):
#   print i, bin(i)

  


