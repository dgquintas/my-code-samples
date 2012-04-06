def factorial(n):
  if n <= 1:
    return 1
  else:
    return n*factorial(n-1)

def sumDigits(n):
  res = sum(map(lambda c: int(c), str(n)))
  return res

if __name__ == "__main__":
  n = factorial(100);
  print sumDigits(n)

