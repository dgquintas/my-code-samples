def digitsum(n):
    s = 0
    while n:
        s += n % 10
        n //= 10
    return s


m = 0
for a in range(2,100+1):
    for b in range(2,100+1):
        ds = digitsum(a**b)
        if ds > m:
            m = ds
            ma, mb = a,b
print(m, ma, mb)


