from itertools import count

# initial observations:
# the first digit of the integer must be a 9 in order to have any chance
# against the given example 9*(1,2,3,4,5) = 918273645
#
# the integer must in addition be < 10000 -the resulting number will be too
# long just after (1,2) and > 9000 (2 and 3 digit numbers would either burst or
# fall short of a 9 digits figure)
#
# all digits of the interger must be different (otherwise they'd be duplicates
# after multiplying by (1,)
# likewise, no zeros allowed


def isPandigital(n):
    s = set("".join( i for i in str(n) ))
    return len(s)==9 and "0" not in s

def getInt(l):
    return int("".join( str(i) for i in l ))


lf = lambda a,b: getInt([a*i for i in range(1,b)])
candidates = ( lf(a,b) 
                for a in range(9123,10000) 
                    for b in range(2,4) 
                        if isPandigital(lf(a,b)) ) 
print( max(candidates) )
