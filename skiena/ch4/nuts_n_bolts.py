# The nuts and bolts problem is defined as follows. You are given a collection
# of n bolts of different widths, and n corresponding nuts. You can test whether a
# given nut and bolt fit together, from which you learn whether the nut is too large,
# too small, or an exact match for the bolt. The differences in size between pairs of
# nuts or bolts are too small to see by eye, so you cannot compare the sizes of two
# nuts or two bolts directly. You are to match each bolt to each nut.
# Give an O(n2 ) algorithm to solve the nuts and bolts problem. Then give a
# randomized O(n log n) expected time algorithm for the same problem.


# The issue here is that we can't just sort both collections, which would render the
# problem trivial: b[i] would pair with n[i] and that's it. We can't because we are
# told that we can't compare elements of the same type with each other. 
#
# Instead, let's try to use a bolt's value as the pivot for the nuts. That'd result
# in a nuts' vector divided in nuts < b to the left and nuts >= b to the right. In 
# fact, during this process, we'll also pinpoint the n[i] s.t. == b[i]. We can use 
# this n[i] as the pivot for the bolts. As usual with the quicksort strategy, these
# n[i] and b[i] won't change position. Using this n[i], we can do the same for the bolts,
# hence dividing it into b's < n[i] and b's >= n[i]

import random
import logging

logging.basicConfig(level=logging.INFO)

def swap(v,i,j):
    v[i], v[j] = v[j], v[i]

def qsort(b, n, ini, end):
    logging.info("Entering with ini = %d, end = %d", ini, end)
    if end-ini > 1:
        # choose a random pivot value from b to be used on n
        a_bolt = random.choice(b[ini:end])
        logging.debug("Chosen %d as bolt pivot", a_bolt)
        logging.debug("nuts before using %d as pivot bolt: %s", a_bolt, n[ini:end])
        a_nut_idx = partition(n, a_bolt, ini, end)
        logging.debug("nuts after using %d as pivot bolt: %s", a_bolt, n[ini:end])
        # nuts vector is now divided in two: those elements
        # < than a_bolt and those >= a_bolt.
        # We have the index, for this nuts vector, of the 
        # nut such that n[a_nut_idx] == a_bolt
        assert(n[a_nut_idx] == a_bolt)
        
        a_nut = n[a_nut_idx]
        logging.debug("nuts[%d] == %d", a_nut_idx, a_nut)
        # we can now use a_nut as the pivot value to partition
        # the bolts! 
        # The resulting bolts vector will share the index position of
        # a_nut (a_nut_idx). Our first solution's "fixed point"
        logging.debug("bolts before using %d as pivot nut: %s", a_nut, b[ini:end])
        a_bolt_idx = partition(b, a_nut, ini, end)
        logging.debug("bolts after using %d as pivot nut: %s", a_nut, b[ini:end])
        assert( b[a_bolt_idx] == a_nut )
        assert( a_bolt_idx == a_nut_idx )

        # right now, we have created two smaller subproblems. 
        # nuts and bolts from ini to a_bolt_idx (or a_nut_idx, they are ==)
        # conform one subproblem. From a_bolt_idx to end, another.
        qsort(b, n, ini, a_bolt_idx)

        # the pivot position (a_bolt_idx) is left alone, as it's at its final
        # position already. Thus we start from pivot+1
        qsort(b, n, a_bolt_idx+1, end)

def partition(v, pv, ini, end):
    # modify v so that all elements less than the given pivot value
    # are clustered towards the left, with the rest >= to the right.

    # we need the index to be able to save the pivot element 
    p = v[ini:end].index(pv) + ini# O(n)
    swap(v, p, end-1) #save pivot 

    evict_idx = i = ini
    while i < end:
        if v[i] < pv:
            swap(v, evict_idx, i)
            evict_idx += 1
        i += 1
    swap(v, evict_idx, end-1) #restore pivot
    return evict_idx

random.seed(1)

N = 10

b = [ random.randint(1,20) for _ in range(N) ]
n = b[:]
random.shuffle(n)

print("b = ", b)
print("n = ", n)

qsort(b,n, 0, N)

print("b = ", b)
print("n = ", n)





