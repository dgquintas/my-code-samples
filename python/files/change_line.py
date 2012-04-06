f = file('file.txt', 'r+b')
pos = 0
for l in f:
  if l.startswith('dos'):
    print pos
    break
  pos += len(l)
f.seek(pos)
f.write('f00')
f.close()
