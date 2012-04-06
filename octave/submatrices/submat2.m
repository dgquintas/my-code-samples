rows = 10; cols=4;
a = reshape(1:rows*cols, rows, cols)
m = rand(1,rows)
n = rows; s = 3;
b = ceil(n/s)
c = zeros(1,cols)

for i=1:b:rows-b+1
  suba = a(i:i+(b-1), :)
  m(:,i:i+(b-1))
  c += m(:,i:i+(b-1))*suba
  printf('\n')
endfor
if(mod(n,s) > 0)
  lastsuba = a(rows-mod(n,s):rows, :)
  c += m(:, rows-mod(n,s):rows) * lastsuba
endif

%c
m*a

