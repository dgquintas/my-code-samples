import string

with open('template.txt') as src, open('output.txt', 'w') as dst:
  input = src.read()
  print("Input:")
  print(input)

  t = string.Template( input )
  res = t.substitute({'value': 'un valor', 
                      'stuff': 'this will be overriden'}, 
                      stuff="shit")
  dst.write(res)
  print("Output:")
  print(res)



