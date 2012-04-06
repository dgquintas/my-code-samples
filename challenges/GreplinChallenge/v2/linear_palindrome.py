from __future__ import division, print_function

# Implementation of longest palindrome substring based on 
# http://www.akalin.cx/longest-palindrome-linear-time
#
# O(n) time is achieved by avoiding extra accesses to the string
# exploiting the symmetry of "subpalindromes" within longer palindromes.
# However, this comes to the cost of O(n) in space

def get_start(i,v):
    """ Returns the palindrome centered at "i" starts 
        in the max. lengths vector "v" 
    """
    return i-v[i]-1
def is_prefix(i,j,v):
    return get_start(i,v) == get_start(j,v)

def is_suffix(v,s):
    """ True if the palindrome at v's tail reaches the end of s """
    c = len(v)-1
    n = len(s)
    return c + v[c] == 2*n

def process(v,s):
    """ Returns the lenght of the next center """
    i = len(v)
    l = i//2 -1
    if i & 0x1: # odd
        res = 1
        r = l + 2
    else:
        res = 0
        r = l + 1
    while l >=0 and r < len(s) and s[l] == s[r]: 
        l -= 1
        r += 1
        res += 2
    return res

def propagate(v,s):
    """ Populates v with what it can be derived from the current center 
        (v's tail)
    """
    # if the palindrome at the current center expends until the
    # end of s, we have a certain length for all subpalindromes
    # to the right of this center
    suffix = is_suffix(v,s)

    # consider the length of the palindrome
    # centered at v's tail in order to further populate
    # v with what we can for sure predict
    l = v[-1]
    c = len(v)-1
    for j in reversed(range(c-l+1, c)):
        pre = is_prefix(c,j,v)
        if not pre or suffix: # we have a definite answer
            v.append(v[j])
        else: # pre and no suffix
            break
            # if it's a prefix, we can only give lower
            # bounds, but we'd have to check the palindrome's
            # length anyway, so we don't get much.

def get_longest_palindrome(v,s):
    """ Given a full vector of palindrome lengths v and the
        problem string s, extract the longest palindromic substring """
    m,j = max( (x,i) for i,x in enumerate(v) )
    start = j//2 - m//2
    return s[start:start+m] 

if __name__ == "__main__":
    v = [0,1] # first and second centers are bound to have those lenghts
    s = file('gettysburg.txt').read()
    n = len(s)

    while len(v) < 2*n+1:
        v.append(process(v,s))
        propagate(v, s)

    print(get_longest_palindrome(v,s))

