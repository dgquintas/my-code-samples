from operator import itemgetter

i = input()
j = input()

def cycleLenght(prevs, n):
    l = 1
    while n != 1:
        if n & 0x1:
            n *= 3
            n += 1
        else:
            n /= 2
        if n in prevs:
            l += prevs[n]
            break
        l += 1
    return l 

lengths = {}
for n in range(i,j+1):
    lengths[n] = cycleLenght(lengths, n)

print( max(lengths.values()) )
    

