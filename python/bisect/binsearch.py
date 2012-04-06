import random
import bisect

l = sorted( random.randint(-1000, 1000) for _ in range(10000) )

n_ctx = 5

def find_1st_of(k):
    i = bisect.bisect_left(l, k)
    print "Index to insert BEFORE the 1st occurrence of %d: %d" % (k, i)
    print "%d ... %d" % (i-n_ctx, i+n_ctx)
    print "%s HERE %s" % (l[i-n_ctx:i], l[i:i+n_ctx])

    j = bisect.bisect_right(l, k) # or just bisect(...)
    print "Index to insert BEFORE the 1st occurrence of %d: %d" % (k, j)
    print "%d ... %d" % (j-n_ctx, j+n_ctx)
    print "%s HERE %s" % (l[j-n_ctx:j], l[j:j+n_ctx])

find_1st_of(0)

from timeit import Timer
iters=10000
print "\nNow for some benchmarking. Will run %d iterations of each testcase" % iters

stmt1 = 'l.index(0)'
stmt2 = 'bisect.bisect_left(l,0)'
t1 = Timer(stmt1, "from __main__ import l")
t2 = Timer(stmt2, "from __main__ import l; import bisect")

print "%s:\t\t %.2f usec/iter" % (stmt1, 1e6 * t1.timeit(number=iters)/float(iters))
print "%s: %.2f usec/iter" % (stmt2, 1e6 * t2.timeit(number=iters)/float(iters))



