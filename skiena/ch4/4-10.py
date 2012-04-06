# Given a set S of n integers and an integer T, give an O(n^{k-1} log n) algorithm
# to test whether k of the integers in S add up to T.
#
# We know how to do it for k=2. It's exercise 4-8. Basically, on a sorted array, 
# iterate over it with two pointers that'll move accordingly to the sum of their
# pointed values being < or > than the required T. 
#
# For k=n, we do it recursively: for the i-th element we consider (we start at 0, 
# over a sorted array), we reduce the problem to finding the k-1 elements in S-S[i] 
# that'd add up to T-S[i]. We may have to consider this subproblem for each of the n 
# elements of the array. 
#
# Therefore, 
#
#          / - O(n) if k=2
# T_k(n) = |
#          \ - T_{k-1}(n) * n if k>2
#
# It's straightforward to see that T(n) = O( n^{k-1} )
# which is even better than the required O( n^{k-1} log n ). The sorting only adds
# a O(n log n) at the beginning, which is totally eclipsed by O(n^{k-1}). The only 
# way to "make it" show up is by sorting only on the base case, hence rendering 
# the base case O(n log n) instead of just O(n). Weiiiiird.

import random

seed = random.randint(1,100)
#seed = 31  #<- no sol for this one
random.seed(seed)
print("Using seed", seed)
S = set([ random.randint(1,100) for _ in range(random.randint(100,200)) ])

S = sorted(S) # S is now a list

def f(k, S, T):
    if T < 0:
        return []
    if k == 2:
        p1 = 0
        p2 = len(S)-1
        while p1 < p2:
            trial = S[p1]+S[p2]
            if trial < T:
                p1 += 1 #add a little. This is the least we can add
            elif trial > T: 
                p2 -= 1 #remove a little. This is the least we can remove
            else: # trial == T. bingo
                return [S[p1], S[p2]]
        else:
            return []
    else: # k > 2
        for i in range(len(S)):
            x = S[i]
            newT = T-x
            subP = f(k-1, S[i+1:], newT)
            if subP:
                res = [x]
                res.extend(subP)
                return res
        else:
            return []


if __name__ == "__main__":
    T = random.randint(1,100)
    k = random.randint(5,10)
    res = f(k, S, T)
    if res:
        print(T, k, res)
        print(len(res), sum(res))
        assert( T == sum(res) )
        assert( k == len(res) )
    else: 
        print("No sol. T = %s, k = %s, S = %s" % (T, k, S))
