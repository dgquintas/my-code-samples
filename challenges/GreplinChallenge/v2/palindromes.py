from __future__ import division, print_function

# This file contains both the naive implementation (Quadratic) and 
# a more complex implementation (Linear) .
#
# It is however interesting to note that these are worst-case 
# bounds: the quadratic (naive) method is not only simpler to implement,
# it also runs in O(1) space -as opposed to O(n) for the linear algorithm-
# and for most inputs (ie, texts with few and short palindromes) it runs in 
# O(n). 
# Refer to the benchmarking results performed. For long inputs with short 
# palindromes ( length palindromes << length text ), the naive quadratic
# algorithm still behaves linearly in expectation. However, the algorithm that's 
# actually linear even in the worst-case falls behind, most likely due to the 
# overhead introduced by the management of the O(n) space. 

class Linear(object):
    """
    Implementation of longest palindrome substring based on 
    http://www.akalin.cx/longest-palindrome-linear-time
    
    O(n) time is achieved by avoiding extra accesses to the string
    exploiting the symmetry of "subpalindromes" within longer palindromes.
    However, this comes to the cost of O(n) in space
    """

    def __init__(self, s):
        self.s = s
        self.v = [0,1] # first and second centers are bound to have those lenghts

    def get_start(self, i):
        """ Returns the palindrome centered at "i" starts 
            in the max. lengths vector "v" 
        """
        return i-self.v[i]-1

    def is_prefix(self,i,j):
        return self.get_start(i) == self.get_start(j)

    def is_suffix(self):
        """ True if the palindrome at v's tail reaches the end of s """
        c = len(self.v)-1
        n = len(self.s)
        return c + self.v[c] == 2*n

    def process(self):
        """ Updates v with the lenght of the next center """
        i = len(self.v)
        l = i//2 -1
        if i & 0x1: # odd
            res = 1
            r = l + 2
        else:
            res = 0
            r = l + 1
        while l >=0 and r < len(self.s) and self.s[l] == self.s[r]: 
            l -= 1
            r += 1
            res += 2
        self.v.append(res)

    def propagate(self):
        """ Populates v with what it can be derived from the current center 
            (v's tail)
        """
        # if the palindrome at the current center expends until the
        # end of s, we have a certain length for all subpalindromes
        # to the right of this center
        suffix = self.is_suffix()

        # consider the length of the palindrome
        # centered at v's tail in order to further populate
        # v with what we can for sure predict
        l = self.v[-1]
        c = len(self.v)-1
        for j in reversed(range(c-l+1, c)):
            pre = self.is_prefix(c,j)
            if not pre or suffix: # we have a definite answer
                self.v.append(self.v[j])
            else: # pre and no suffix
                break
                # if it's a prefix, we can only give lower
                # bounds, but we'd have to check the palindrome's
                # length anyway, so we don't get much.

    def get_longest_palindrome(self):
        """ Given a full vector of palindrome lengths v and the
            problem string s, extract the longest palindromic substring """
        m,j = max( (x,i) for i,x in enumerate(self.v) )
        start = j//2 - m//2
        return self.s[start:start+m] 
    
    def solve(self):
        del self.v[:]
        n = len(self.s)
        while len(self.v) < 2*n+1:
            self.process()
            self.propagate()

        return self.get_longest_palindrome()


class Quadratic(object):
    def __init__(self, txt):
        self.txt = txt

    def checkOdd(self, i):
      #  C    D    C 
      #(i-1)  i  (i+1)
      j = 1
      while (i-j) >= 0 and \
            (i+j) < len(self.txt) and \
                    self.txt[i-j] == self.txt[i+j]: 
                        j += 1
      return (2*j-1, self.txt[i-j+1:i+j])

    def checkEven(self, i):
      #  C    C
      #  i  (i+1)
      j = 1
      while (i-j) >= 0 and \
            (i+j+1) < len(self.txt) and \
            self.txt[i-j] == self.txt[i+j+1]: 
                j += 1
      return (2*j, self.txt[i-j+1:i+j+1])

    def solve(self):
        i=1
        word = ''
        while i  < len(self.txt)-1:
          if self.txt[i-1] == self.txt[i+1]:
            check = self.checkOdd
          elif self.txt[i] == self.txt[i+1]:
            check = self.checkEven
          else:
            check = None

          if check:
            j, w = check(i)
            i += 1
            if len(w) > len(word):
              word = w
          else:
            i+=1
         
        return word 

if __name__ == "__main__":
    files = ['gettysburg.txt', 'long.txt']
    for f in files:
        txt = file(f).read()
        quad = Quadratic(txt)
        lin = Linear(txt)

        print("Linear's solution: ", lin.solve())
        print("Quadratic's solution: ", quad.solve())

        from timeit import Timer
        tquad = Timer("quad.solve()", "from __main__ import quad")
        tlin = Timer("lin.solve()", "from __main__ import lin")

        iters = 100
        qt = iters/tquad.timeit(number=iters)
        lt = iters/tlin.timeit(number=iters)
        print( "Linear: invocations/sec", lt )
        print( "Quadratic: invocations/sec", qt )

