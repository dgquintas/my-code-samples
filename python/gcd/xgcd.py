def extendedGCD(a,b):
  if a % b == 0:
    return (0,1)
  else:
    x, y = extendedGCD(b, a % b)
    return (y , x-y*(a // b)) #division entera

inv, _ = extendedGCD(150, 61)
print inv 
print (150*inv) % 61
