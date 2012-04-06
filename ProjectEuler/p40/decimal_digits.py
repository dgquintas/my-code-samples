from functools import reduce

l = (str(i) for i in range(0,1000000))
s = ''.join(l)
print(reduce( lambda x,y: x*y, 
        (int(s[i]) for i in (1,10,100,1000,10000,100000,1000000) )))
