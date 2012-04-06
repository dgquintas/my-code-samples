class C:
    def __pow__(self,b,m=1):
        print " b = ", b, " m = ", m
        return

c = C()
c**3
pow(c,2,3)
