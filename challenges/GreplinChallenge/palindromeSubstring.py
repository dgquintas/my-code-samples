txt = file('gettysburg.txt').read()
#txt = file('long.txt').read()

def checkOdd(i):
  #  C    D    C 
  #(i-1)  i  (i+1)
  j = 1
  while (i-j) >= 0 and (i+j) < len(txt) and txt[i-j] == txt[i+j]: j += 1
  return (2*j-1, txt[i-j+1:i+j])

def checkEven(i):
  #  C    C
  #  i  (i+1)
  j = 1
  while (i-j) >= 0 and (i+j+1) < len(txt) and txt[i-j] == txt[i+j+1]: j += 1
  return (2*j, txt[i-j+1:i+j+1])


i=1
word = ''
while i  < len(txt)-1:
  if txt[i-1] == txt[i+1]:
    check = checkOdd
  elif txt[i] == txt[i+1]:
    check = checkEven
  else:
    check = None

  if check:
    j, w = check(i)
    i += 1
    if len(w) > len(word):
      word = w
  else:
    i+=1
 
print word 

