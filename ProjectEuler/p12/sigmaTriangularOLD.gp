TARGET = 500
tn = n = 0; 
X=1;
while(true, \
  triangNum = (X^2 + X)/2; \
  numDivs = sigma(triangNum,0);   \
  if( numDivs > TARGET,  \
    tn = numDivs; n = X; break;   \
  );  \
  X++; \
) ;
print("tn = ", tn, "; n = ", n);
print("answer (the triangular number): ", triangNum);
quit();
