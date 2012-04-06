def numsToColonNotation(nums):
  #gotta insert a : every two number, except for the last
  #group.
  g = ( nums[i:i+2] for i in xrange(0, len(nums), 2) )
  return ':'.join(g)

def colonNotationToNums(mac):
  g = ( mac[i] for i in xrange(len(mac)) if (i+1) % 3 ) 
  return ''.join(g)

m = "00:0C:F1:29:71:B0"
n = "000CF12971B0"

res = numsToColonNotation(n)
assert res == m
print res

res = colonNotationToNums(m)
assert res == n
print res
