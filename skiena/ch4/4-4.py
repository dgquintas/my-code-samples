from __future__ import print_function 
# Assume that we are given n pairs of items as input, where the first item is a
# number and the second item is one of three colors (red, blue, or yellow).
# Further assume that the items are sorted by number. Give an O(n) algorithm to
# sort the items by color (all reds before all blues before all yellows) such
# that the numbers for identical colors stay sorted.  For example: (1,blue),
# (3,red), (4,blue), (6,yellow), (9,red) should become (3,red), (9,red),
# (1,blue), (4,blue), (6,yellow).

pairs = ( (1,'blue'), (3,'red'), (4,'blue'), (6,'yellow'), (9,'red') )

# as the input is already sorted by the number, we only have to 
# "route" the pairs by color. 

res_dict = {}
for pair in pairs:
    v = res_dict.setdefault(pair[1], [])
    v.append(pair)

print( res_dict['red'] + res_dict['blue'] + res_dict['yellow'] )
print( reduce(lambda a,b: a+b , ( res_dict.get(color) for color in ('red', 'blue', 'yellow'))))
