
S = 9
bricks = (2,3)

def getPartitions(soFar=0, partition=[], partitions=[]):
  for brick in bricks:
    newL = soFar + brick
    if newL < S:
      partition.append(brick)
      getPartitions(newL, partition[:])
      del(partition[-1])
    elif newL == S:
      partition.append(brick)
      partitions.append(partition)
    else: # newL > S
      break
  return partitions

def hasNoCracks(p1,p2):
  pairWiseSum1 =  map( lambda x,y: x+y, p1[1:], p1[:-1])
  pairWiseSum2 =  map( lambda x,y: x+y, p2[1:], p2[:-1])
  print pairWiseSum1, pairWiseSum2
  for i in pairWiseSum1:
    if i in pairWiseSum2:
      return False
  return True

DEPTH = 3

def getWalls(pIni, depth, partitions, wall,walls=[]):
  if depth == DEPTH:
    #walls.append(wall)
    print wall
  else:
    for p2 in partitions:
      if hasNoCracks(pIni,p2):
        wall.append(p2)
        getWalls(p2, depth+1, partitions, wall)
        print pIni, "casa con", p2
        del(wall[-1])


partitions = getPartitions()
for p in partitions:
  assert sum(p) == S
from pprint import pprint
print len(partitions)
pprint(partitions)

print hasNoCracks(partitions[4], partitions[0])

#wall = [partitions[0]]
#
#walls = getWalls(partitions[0], 1, partitions, wall)

#pprint( walls)
