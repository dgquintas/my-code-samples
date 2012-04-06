# The idea is to follow the Fisher-Yates algorithm, which is:
#
# We have a list of elements to be shuffled, length n. 
# 1) Let k be a random number between 0 and n-1 (inclusive)
# 2) Note down the k-th number that wasn't already crossed out
#    somewhere else and crossed it out in the original list
# 3) k--
# 4) repeat if k > 0
#
# This is O(n^2) if implemented as-is. A more computer friendly version in
# O(n) is due to Richard Durnsternfeld and presented in TAOCP Vol. 2 (Alg. P
# pag. 145-146). The main idea is to divide the input array in two sections: 
# elements that haven't already been considered and the "scratchpad" were we
# jot down the shuffled sequence. 

from random import randint
def fisher_yates_shuffle(seq_src):
    seq = list(seq_src)
    n = len(seq)
    i = n-1
    while i > 0:
        j = randint(0, i) #both endpoints are inclusive
        # we have chosen the j-th element among the unprocessed 
        # ones for the next element in the shuffle. Add it to 
        # the shuffle then (from i..end)
        seq[i], seq[j] = seq[j], seq[i] #swap
        i -= 1
    # at this point i == 0, which means the whole array is shuffled
    return seq

n = 20
src = range(n)
shuffled = fisher_yates_shuffle(src)
print(shuffled)
        
# the definition of a proper shuffle is that every shuffle must have the same probability
# of happening. That is, each would happen 1/n! times on average. 
# Conversely, it means that any element from the original array has a probability 1/n of
# happening at any position in the shuffle.

from collections import Counter
c = Counter()
ITERS = 10000
lots_of_shuffles = ( fisher_yates_shuffle(src) for _ in range(ITERS))
# check number of times each element shows up at every position
counters = [ Counter() for _ in range(n) ]
for shuffle in lots_of_shuffles:
    for i,e in enumerate(shuffle):
        counters[i][e] += 1

print("Every element should happen about %f times for each position" % ((1.0/n)*ITERS))
for i in range(n):
    print("For position %d: " % i, counters[i])

