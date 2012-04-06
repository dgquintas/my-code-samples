poly=x^2 + a*x + b;
/* b must be prime, because poly(0) (= b) has to 
be prime */
bound=1000;
maxSeq = -1;
ab=0;
forstep(a=-bound-1, bound-1, 2, \
  forprime(b=0, bound, \
    x=0; \
    while(1, \
      if( isprime(eval(poly)), \
        x++, \
        break \
      ) \
    ); \
    if( x > maxSeq,  \
      maxSeq = x; \
      ab = a*b; \
    );  \
  ) \
); 
print(maxSeq);
print(ab);
quit();
