from __future__ import print_function
import re
import sys
import itertools

def getRE(pattern):
    cre = re.compile(pattern)
    return lambda w: not re.search(cre, w)

if __name__ == "__main__":
    isL, isR = [ getRE(p) for p in ('[yuiophjklnm0-9]', '[qwertasdfgzxcvb0-9]') ]
    lefts, rights = set(),set()
    dictPath = sys.argv[1]
    with open(dictPath) as f:
        for word in f:
            word = word.strip()
            if isL(word):
                lefts.add(word)
            elif isR(word):
                rights.add(word)

    print(lefts)
    print(rights)

    print("%d lefties\n%d righties" % (len(lefts), len(rights)))



