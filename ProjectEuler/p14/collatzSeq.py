cache = {}

def f(n):
  if n & 1: #odd
    res = 3*n +1
  else:
    res = n / 2
  return res

if __name__ == "__main__":
  from itertools import count
  lmax = imax = 0
  for i in range(1,1000000):
    if i % 10000 == 0:
      print (i/1000000.0) * 100, "%"
    if cache.has_key(i):
      l = cache[i]
    else:
      n = i
      l = 1 
      while( n != 1 ):
        n = f(n)
        if cache.has_key(n):
          l += cache[n]
          break
        else:
          l += 1
      cache[i] = l
#    print i, " -> ", l
    if l > lmax:
      lmax, imax = l, i

  print imax, lmax


