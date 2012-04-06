# let's present the different "products" in a table. For 
# X = [2,3,4,5,6,7]
#
#   3*4*5*6*7
# 2  *4*5*6*7
# 2*3  *5*6*7
# 2*3*4  *6*7
# 2*3*4*5  *7
# 2*3*4*5*6
#
# Note that the factors at the right of the diagonal can be
# generated in O(n), saving all the intermediate results 
# [7, 7*6, 7*6*5...] 
# Likewise for the left side. In this case, we don't even
# need to store them, just keep a running total of the left
# side results. Then, for each Xi, after it's been multiplied to the
# left-side-running-total, multiply it by the corresponding 
# "cached" right factor. Voila.


from __future__ import print_function
import random



random.seed(0)
n = 6

X = [ random.randint(1,10) for _ in range(n) ]
print(X)

# O(n)
def getPartialRightFactors(X):
    factors = []
    p = 1
    factors.append(1)
    for i in X[:0:-1]:
        p *= i
        factors.append(p)
    return factors

rightFactors = getPartialRightFactors(X) 
M = []
prev = 1
for i,v in enumerate(X):
    left = prev 
    right = rightFactors[-i-1]
    M.append(left * right)
    prev *= v;


print(M)

