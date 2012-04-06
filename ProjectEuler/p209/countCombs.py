def N(n):
    if n == 1 or n == 0:
        return n
    elif n == 2:
        return 3
    else:
        return N(n-1) + N(n-2)

print list(enumerate( map(N, range(10)) ))
