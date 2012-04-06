print "(period, d as in 1/d) ->", \
  max([ (Mod(10,d).multiplicative_order(), d) 
    for d in primes(11,999)])
