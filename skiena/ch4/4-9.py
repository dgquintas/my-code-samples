from __future__ import print_function
# Give an efficient algorithm to compute the union of sets A and B, where n =
# max(|A|,|B|). The output should be an array of distinct elements that form
# the union of the sets, such that they appear exactly once in the union.
#
# (a) Assume that A and B are unsorted. Give an O(nlogn) algorithm for the problem.
# (b) Assume that A and B are sorted. Give an O(n) algorithm for the problem.

# Let's assume A and B are sorted and that A is the largest set.
# idea: start with the smallest element of A. Add to the result all the elements
# from B smaller than it. If we hit an element of B that's equal, we skip it. When we 
# hit a larger one, we reverse roles.
#
# Hmmm... actually, what I've just described is a freaking merge! The only
# difference is that when we find equal values, only one copy is added.

import random

A = set([ random.randint(1,100) for _ in range(random.randint(100,200)) ])
B = set([ random.randint(1,100) for _ in range(random.randint(100,200)) ])

A = sorted(A)
B = sorted(B)

res = []
i = j = 0
last = None
while j < len(B) and i < len(A):
    if A[i] < B[j]:
        res.append(A[i])
        i += 1
    elif A[i] == B[j]:
        if last != A[i]:
            res.append(A[i])
            last = A[i]
        i += 1
        j += 1
    else: # A[i] > B[j]
        res.append(B[j])
        j += 1

# if there's still something left in either one...
if i < len(A):
    for e in A[i:]:
        res.append(e)
if j < len(B):
    for e in B[j:]:
        res.append(e)

u = set(A).union(set(B))
assert( len(u) == len(res) )
for i in range(len(u)):
    assert( res[i] in u )

    


