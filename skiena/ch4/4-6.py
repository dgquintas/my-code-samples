from __future__ import print_function
# Given two sets S1 and S2 (each of size n), and a number x, describe an O(n
# log n) algorithm for finding whether there exists a pair of elements, one
# from S1 and one from S2, that add up to x. (For partial credit, give a O(n^2)
# algorithm for this problem.)

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
# We'll stop when we've exhausted both S1 and S2 (which will happen at the same time, 
# both being of size n)

import random
try:
    input = raw_input
except:
    pass

N = 10

random.seed(0)
S1 = [ random.randint(1,20) for _ in range(N) ]
S2 = [ random.randint(1,20) for _ in range(N) ]

S1.sort()
S2.sort()

print(S1)
print(S2)


i = 0
j = N-1

x = int(input("x? "))

while i < N and j >=0 :
    s = S1[i] + S2[j]
    if s == x:
        print(i, j, " - ", S1[i], S2[j])
        break
    elif s < x:
        # increment "small element" pointer
        i += 1
    else: # s > x
        # decrement "large element" pointer
        j -= 1


