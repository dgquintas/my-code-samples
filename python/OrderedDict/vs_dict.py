from itertools import count
from collections import OrderedDict

c = count()

def ordered():
    return OrderedDict((
         ('id', next(c)), 
         ('mediatype', next(c)), 
         ('data', OrderedDict((
             ('attachment', next(c)), 
             ('caption',next(c) ), 
         ))), 
         ('author',next(c) ),
         ('when',next(c) ),
         ('source',next(c) ),
         ('location',next(c) ), 
         ('geo', OrderedDict((
             ('lat',next(c) ), 
             ('long',next(c) ), 
             ('coarse',next(c) ), 
         ))), 
         ('score',next(c) ), 
         ('versions',next(c) ),
         ('event',next(c) ), 
        ))

def normal():
    return {
         'id': next(c), 
         'mediatype': next(c),
         'data': {'attachment': next(c), 'caption': next(c)},
         'author':next(c),
         'when':next(c),
         'source':next(c),
         'location':next(c), 
         'geo': {'lat': next(c), 'long': next(c), 'coarse': next(c)},
         'score':next(c), 
         'versions':next(c),
         'event':next(c), 
        }

import sys
o = ordered()
n = normal()
print(sys.getsizeof(o))
print(sys.getsizeof(n))


