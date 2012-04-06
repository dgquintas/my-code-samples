TARGET = 500
tn = n = 0; 
X=1;
while(true, \
  /* odd */ numDivs = sigma(X,0)*sigma((X+1)/2,0); \
  if( numDivs > TARGET,  \
    tn = numDivs; n = X; break;   \
  );  \
  X++; \
 /* even */ numDivs = sigma(X/2, 0)*sigma(X+1, 0);  \
  if( numDivs > TARGET,  \
    tn = numDivs; n = X; break;   \
  );  \
  X++; \
) ;
print("tn = ", tn, "; n = ", n);
triangNum = (n^2 + n)/2; 
print("answer (the triangular number): ", triangNum);
quit();
