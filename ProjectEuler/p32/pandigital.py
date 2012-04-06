import itertools

# the sizes of the multiplicands/operand can only be 3,2,4 and 1,4,4. This
# is calculated by taking into account that the number of digits from a product of
# a,b multiplicant digit count is <= (a+b+1).

def list_to_int(l):
  return int(''.join( map(str, l) ))

def pandigital(digits, n):
  nums = []
  for c in itertools.combinations(digits, n):
    for p in itertools.permutations(c):
      nums.append(list_to_int(p))
  return nums


def get_pandigitals_for_sizes(A,B):
  C = 9-A-B;
  res = set()
  
  digits = range(1,10)
  pdA = pandigital(digits,A)
  for a in sorted(pdA):
    digits2 = list(digits)
    for d in str(a):
      if int(d) in digits2:
        digits2.remove(int(d))

    pdB = pandigital(digits2, B)
    for b in sorted(pdB):
      digits3 = list(digits2)
      for dd in str(b):
        if int(dd) in digits3:
          digits3.remove(int(dd))
      pdC = pandigital(digits3, C)
      prod = a*b
      if len(str(prod)) > 4: 
        break #we can stop because the multiplicants are sorted: 
              #any remaining product will also be too large
      if prod in pdC:
        print '\t\t%d * %d = %d' % (a,b,prod)
        res.add(prod)
  return res

res = get_pandigitals_for_sizes(2,3)
res.update( get_pandigitals_for_sizes(1,4) )

print sum(res)

