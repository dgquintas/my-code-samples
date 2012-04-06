from heapq import *

items = [(1, 'foo'), (12.3, 'bar'), (0, 'min')]
h = []
for i in items:
    heappush(h, i)

print("Raw heap:", h)
print("Min:", heappop(h))
