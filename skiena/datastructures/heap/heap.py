# always work with indices!!!

def bubbleUp(data, i):
    if i > 0:
        p = getParentIdx(i)
        if data[i] < data[p]:
            data[i], data[p] = data[p], data[i]  #swap
            bubbleUp(data, p)

def bubbleDown(data, i):
    left = getLeftChildIdx(i)
    right = left+1

    if left >= len(data):
        return

    if right >= len(data) or data[left] < data[right]:
        dominant = left
    else:
        dominant = right
        
    if data[dominant] < data[i]:
        data[i], data[dominant] = data[dominant], data[i]
        bubbleDown(data, dominant)
        
def getParentIdx(i):
    return (i-1)//2

def getLeftChildIdx(i):
    return 2*i + 1


class Heap(object):

    def __init__(self):
        self._data = []

    def __getitem__(self, i):
        return self._data[i]

    def __len__(self):
        return len(self._data)

    def __repr__(self):
        return str(self._data)

    def push(self, v):
        # new element is appended to the end of the
        # internal array. 
        # Then it's gotta "bubble up" to wherever it belongs
        self._data.append(v)
        bubbleUp(self._data, len(self._data)-1)

    def pop(self):
        #remove first element from array. Put last element 
        #in its place. And then push this element down 
        #until the dominance balance is restored
        res = self._data[0]
        self._data[0] = self._data[-1]
        bubbleDown(self._data, 0)

        return res

    def getMin(self):
        return self._data[0]


import random
random.seed(0)

h = Heap()

data = [ random.randint(1,20) for _ in range(10) ]
print(data)

for i in data:
    h.push(i)

print(str(h))

sortd = [h.pop() for i in range(len(h))]
print(sortd)
print(sorted(data))

assert( sortd == sorted(data))


