coins = (1,2,5,10,20,50,100,200)

def count(n,m):
  if n == 0:
    return 1
  if n < 0:
    return 0
  if ( m < 0 and n >= 1):
    return 0

  return count( n, m-1 ) + count(n-coins[m], m)


print( count(200, 7) )

