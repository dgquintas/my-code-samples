# split the ciphertext in three columns (because we are told the key is 3 chars long) 
# for each column, pick the most common character. We presume that in the plaintext, that'd be the space (dec 20)
# by XORing this most common char with 20, we may be able to get the key (by virtue of XOR being its own inverse)

from __future__ import print_function 

def oldSkool(): #works with older versions of python
    with open('cipher1.txt') as f:
        cipherText = f.read().strip().split(',')
        colCounts = [ {}, {}, {} ]
        for i,c in enumerate(cipherText):
            d = colCounts[i%3]
            count = d.setdefault(c,0)
            d[c] = count + 1

        sortedCounts = [ sorted(col.items(), key= lambda x: x[1], reverse=True) for col in colCounts ]
        mostFreq = [ int(col[0][0]) for col in sortedCounts ] 

        return ''.join([ chr(c ^ 32) for c in mostFreq]) 


def newSkool(): #python >= 2.7
    from collections import Counter
    with open('cipher1.txt') as f:
        cipherText = f.read().strip().split(',')
        colCounts = [ Counter() for _ in range(3) ]
        for i,c in enumerate(cipherText):
            colCounts[i%3][c] += 1

        mostFreq = [ int(col.most_common(1)[0][0]) for col in colCounts] 
        return ''.join([ chr(c ^ 32) for c in mostFreq]) 



if __name__ == "__main__":
    import sys
    if sys.version_info.major >= 3 or sys.version_info.minor >= 7:
        print(newSkool())
    else:
        print(oldSkool())
        



