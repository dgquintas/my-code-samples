# We have an input array with N elements. We want to extract a random sample 
# of n elements. Meaning that every element in the random sample has a probability
# n/N of being there (this is akin to saying: what's the prob of getting an even 
# number out of a one throw of a dice: #(even)/#(total). Or, seen from the perspective
# of the individual elements: each one of them thinks "Oh, there'll be n of us in that
# sample, therefore I have n chances to get selected"). 
#
# HOWEVER, the probability changes as the samples get selected. The selection of the
# sample's element is dependent on previous selections. Having selected previously 
# ocurring elements impacts the current one. For instance, at the second input record, 
# we may be in one of the following:
#
# 1) the first element was selected. Only n-1 slots remain for the rest of the sample. 
# And now there are N-1 remaining input records to consider.
# 2) the first element was NOT selected. All n sample slots are still available but
# the number of candidates has been reduced to N-1. 
#
# What this implies is that we have to revisit the probability of a given input record
# being chosen after each step. Let's think in terms of what's the probability of the
# (t+1)th input record being selected, after having already selected m previous records
# for the sample. The number of available options we have is C(N-t, n-m), the ways to 
# select the remaining sample slots out of the remaining input records. Out of those 
# options, C(N-(t+1), n-(m+1)) DO select the (t+1)th element. Therefore, the probability
# of the (t+1)th input record being selected is the quotient of the latter by the former:
#
# C(N-(t+1), n-(m+1)) / C(N-t, n-m) = (n-m) / (N-t)
#
# which means that, for each input record, we should select it with probability (n-m)/(N-t)
#
# We can prove that this is correct (that every element is chosen with a probability 
# n/N) by induction (t are the number of input recs already processed and m the number of
# sample slots used):
#
# Base case: first element is chosen with prob (n-0)/(N-0) = n/N 
# For the second input element, we have two options:
# 1) first element was chosen: m=1, t=1
# 2) first element was not chosen: m=0, t=1
#
# the probability of the second element being chosen equals:
# P(2nd elem chosen) = P(choose 2nd after NOT having chosen 1st) + 
#                      P(choose 2nd after having chosen 1st) =
#                      [(n)  /(N-1)]*[1-n/N] + [(n-1)/(N-1)]*[n/N] = n/N
# 
# and so forth for 3rd, etc etc. 
# and now, for the actual algorithm:

from random import random
def random_sample(inp, n):
    N = len(inp)
    m = t = 0
    sample = []
    for i in inp:
        if random() * (N-t) < (n-m):
            sample.append(i)
            m += 1
        if n-m <= 0:
            break
        t += 1
    return sample

# In order to make sure that the sample is really random, we must verify that every
# input element has a chance of n/N of being in the sample. ie, that every number
# in the input, for a large enough number of samples, shows up on average n/N times. 
from collections import Counter
c = Counter()

N = 1000
n = 50
ITERS = 100000
inp = range(N)
lots_of_samples = ( random_sample(inp, n) for _ in range(ITERS) )
for sample in lots_of_samples:
    for elem in sample:
        c[elem] += 1

from pprint import pprint
pprint(dict(c))
print("Each element should have showed up about %f times" % ((float(n)/N)*ITERS))
