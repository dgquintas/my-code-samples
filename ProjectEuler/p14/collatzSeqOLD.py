def f(n):
  if n & 1: #odd
    n = 3*n +1
  else:
    n = n / 2;
  return n

if __name__ == "__main__":
  from itertools import count
  lmax = imax = 0
  for i in range(1,100000):
    l = 0
    n = f(i)
    while( n != 1 ):
      l += 1
      n = f(n)
    if l > lmax:
      lmax, imax = l, i

  print imax, lmax


