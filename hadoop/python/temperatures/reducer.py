#!/usr/bin/env python

# input is of the type
# 1949	+0111
# 1949	+0078
# 1950	+0000
# 1950	+0022
# 1950	-0011
 
import sys

(last_key, max_val) = (None, 0)

for line in sys.stdin:
    (key, val) = line.strip().split("\t")
    if last_key and last_key != key:
        # we've just changed key
        # print max val for the key we've just left
        print("%s\t%s" % (last_key, max_val))
        (last_key, max_val) = (key, int(val))
    else:
        (last_key, max_val) = (key, max(max_val, int(val)))

if last_key:
    print("%s\t%s" % (last_key, max_val))





