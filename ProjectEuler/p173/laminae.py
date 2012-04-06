# the idea is to count how many tiles are needed to cover a "hole" of side
# h. It doesn't have to be a hole, as after the first "iteration", it'd be
# composed of the empty space plus a 1-tile-thick square of tiles. 
# It's easy to see that 4(h+1) tiles are needed to suround a square (hole)
# of side h. Once that's been surounded, the next square to suround will
# have a side 2 units larger. 
# In general, the number of tiles used after n steps is
# sum( 4(h+1) + 8i ) para i=0..n. As there always has to be a hole,
# h >= 1. The largest possible hole is given by l/4 -1 , for l the number 
# of available tiles. 

#Solving for n in the sum, we end up with the number of possible laminae
#for each hole size.

from math import sqrt

print(sum( int(0.5*(sqrt(h*h + 1000000) -h-2)) + 1 for h in range(1,250000) ))
