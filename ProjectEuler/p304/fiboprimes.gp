\\idea: to calculate the nth fibonacci number by 
\\exponentiation of the fibonacci matrix composed by
\\modular integers. 
\\the successive exponentiations of this matrix for
\\the diferent values of a(i) (basically, the series of
\\primes > 10^14) uses the delta a[i]-a[i-1], given that
\\ A^(n+m) = A^n * A^(m-n)

m = 1234567891011;
A = [ Mod(1,m), Mod(1,m); Mod(1,m), Mod(0,m) ];

\\np = nextprime(10^14);
\\primesL = listcreate(100001);
\\listput(primesL, np);
\\for(X=1,100000, \
\\    np=nextprime(np+1); \
\\    listput(primesL, np);)
\\##
\\print(primesL);

np = nextprime(10^14)
Ai = A^(np);
s = Ai[1,2];
for(i=2,100000, \
  nnp = nextprime(np+1); \
  delta = nnp-np; \
  Ai = Ai * A^delta; \
  s += Ai[1,2]; \
  np = nnp;)
  
print(lift(s))

quit()
