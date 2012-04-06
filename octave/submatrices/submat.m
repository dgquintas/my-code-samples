rows = 4; cols=10;
a = reshape(1:rows*cols, rows, cols)
m = rand(1,rows)
n = cols; s = 3;
b = ceil(n/s)
c = []

for i=1:b:cols-b+1
  suba = a(:,i:i+(b-1))
  c = [c m*suba];
  printf('\n')
endfor
if(mod(n,s) > 0)
  lastsuba = a(:,cols-mod(n,s):cols)
  c = [c m * lastsuba]
endif

c
m*a

