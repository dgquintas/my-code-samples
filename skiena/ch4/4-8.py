#  Given a set of S containing n real numbers, and a real number x. We seek an
#  algorithm to determine whether two elements of S exist whose sum is exactly
#  x.
# (a) Assume that S is unsorted. Give an O(n log n) algorithm for the problem.
# (b) Assume that S is sorted. Give an O(n) algorithm for the problem.


# this is very similar to 4-6. We now have just one array instead of two, but the idea
# is the same.
# For (a), we sort and get to (b)
# For (b), I mostly repeat what I wrote for 4-6

# the O(n lg n) complexity hints sorting. 
# Let's consider too pointers, one pointing at the first element and the other one
# at the last. There can be three scenarios:
# 1) The sum of the pointed values equals the value we want (x). that's it
# 2) the sum is < x
# 3) the sum is > x
#
# In case of 2), the only option we have is to add more stuff. The best option we have
# for that is to add the second-smallest element, by incrementing the left pointer. 
# We try recursively again. 
#
# In case of 3), we have to remove stuff. Conversely then, we decrement the right pointer
# and recurse. 
#
# The base case of the recursion is clearly when both left and right pointers are equal 
# (or, being on the safer side, when left >= right)

import random
try:
    input = raw_input
except:
    pass

N = 10

random.seed(0)
S = [ random.randint(1,20) for _ in range(N) ]

S.sort()

print(S)

i = 0
j = N-1

x = int(input("x? "))

# if S were already sorted, the following is clearly O(n). In fact, it's O(n/2) !
while i < j:
    s = S[i] + S[j]
    if s == x:
        print((i, j), " - ", (S[i], S[j]))
        break
    elif s < x:
        # increment "small element" pointer
        i += 1
    else: # s > x
        # decrement "large element" pointer
        j -= 1

