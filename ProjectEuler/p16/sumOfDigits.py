def sumDigits(n):
  res = sum(map(lambda c: int(c), str(n)))
  return res

if __name__ == "__main__":
  n = 2**1000;
  print sumDigits(n)

