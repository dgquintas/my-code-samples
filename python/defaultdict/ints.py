from collections import defaultdict

ddzero = defaultdict(int)
ddzero['foo'] += 10

dd_n = defaultdict( lambda: 'foo' )
print("%(foo)s - bar" % dd_n )
