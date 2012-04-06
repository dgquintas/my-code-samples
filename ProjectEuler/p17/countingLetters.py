class LengthInLetters(object):
    def __init__(self):
        self.cache = {}
        self.cache[0] = 0
        self.cache[1] = self.cache[2] = self.cache[6] = self.cache[10] = 3
        self.cache[4] = self.cache[5] = self.cache[9] = 4
        self.cache[3] = self.cache[7] = self.cache[8] = 5
        self.cache[15] = 7
        self.cache[11] = self.cache[12] = 6
        self.cache[13] = self.cache[14] = 8
    def __call__(self, n):
        if n < 16:
            return self.cache[n]
        if 16 <= n <= 19:
            if n == 18:
                return 8
            else:
                return self(n % 10) + 4
        if 20 <= n <= 29:
            return self(n % 10) + 6
        if 30 <= n <= 39:
            return self(n % 10) + 6
        if 40 <= n <= 49:
            return self(n % 10) + 5
        if 50 <= n <= 59:
            return self(n % 10) + 5
        if 60 <= n <= 99:
            decs = self(n // 10) 
            if n // 10 == 8:
                decs += 1
            else:
                decs += 2
            return decs + self(n % 10) 

        if 100 <= n <= 999:
            res = self( n // 100 ) + 7 + self(n % 100) 
            if n % 100 != 0:
                res += 3
            return res

        if n == 1000:
            return 11

instance = LengthInLetters()
print sum( instance(i) for i in xrange(1,1000+1) )




