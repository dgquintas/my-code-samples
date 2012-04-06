def gcdEuclides(a,b):
  if a < b:
    b, a = a, b
  while b:
    a, b = b, a % b
  return a


print gcdEuclides(-150, 61)
