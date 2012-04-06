from fractions import Fraction

def form1():
    res = Fraction(1)
    # ix / xj
    for x in range(1,10):
        for i in range(1,10):
            for j in range(1,10):
                if i == j:
                    continue
                num = ((10*i)+x)
                den = ((10*x)+j)
                a = Fraction(num, den)
                b = Fraction(i,j)
                if a == b:
                    print('%d%d / %d%d' % (i,x,x,j))
                    res *= a
    print( res.denominator )




form1()
