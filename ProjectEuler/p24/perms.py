def permutations(L):
    if len(L) <= 1:
        yield L
    else:
        a = [L.pop(0)]
        for p in permutations(L):
            for i in range(len(p)+1):
                yield p[:i] + a + p[i:]


l = list( permutations( map(str, xrange(10)) ) ) 
l= map("".join, l)
l.sort()
print l[1000000-1]

