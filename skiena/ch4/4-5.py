from __future__ import print_function 
# The mode of a set of numbers is the number that occurs most frequently in the
# set. The set (4, 6, 2, 4, 3, 1) has a mode of 4. Give an efficient and correct
# algorithm to compute the mode of a set of n numbers.

import logging
import random

logging.basicConfig(level=logging.INFO)

inp = [random.randint(1,100) for _ in range(2000)]

def with_dict():
    from collections import Counter
    # this obviously works. However, the dict will be O(n) (if most elements are unique)
    # Time complexity is O(n) though.
    c = Counter(inp)
    return c.most_common(1)

def with_sorting():
    #another option is to sort ( O(n lg n) ) and traverse the array noting which element has
    #the longest consecutive run
    inp_sorted = sorted(inp)
    i = 0
    mode = None
    longest_run = 0
    n = len(inp_sorted)

    while i < n:
        count = 0
        v = inp_sorted[i]
        j = i+1
        while j < n and inp_sorted[j] == v:
            j += 1
        count = j-i
        i = j 
        logging.debug("Count for %d: %d", v, count)
        if count > longest_run:
            longest_run = count
            mode = v

    return (mode, longest_run)


if __name__ == '__main__':
    from timeit import Timer
    ITERS = 10000
    funcs = ('with_dict', 'with_sorting')
    for f in funcs:
        t = Timer("%s()" % f, "from __main__ import %s" % f)
        msecs_to_execute_n_times = t.timeit(number=ITERS) * 1000
        logging.info("%s:\t%f secs per run",f, msecs_to_execute_n_times/ITERS)

