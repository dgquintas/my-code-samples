# the idea is to have a hierarchical tree of Events. The leaves are
# Directives, containing the logic that determines if a certain something
# falls into the event defined by the path from the root to that directive.
from pprint import pprint, pformat
import itertools
import re
import collections
import abc

Match = collections.namedtuple('Match','path, matches')

class _Node(object):
    __metaclass__ = abc.ABCMeta

    def __init__(self, name):
        self._name = name
        self._parent = None

    @property
    def name(self):
        return self._name

    @property
    def path(self):
        if self.parent:
            return self.parent.path + '.' + self.name
        else:
            return self.name
    
    @property
    def parent(self):
        return self._parent

    @parent.setter
    def parent(self, p):
        self._parent = p

class _Directive(_Node):
    __metaclass__ = abc.ABCMeta

    def __init__(self, name, type, args):
        super(_Directive, self).__init__(name)
        self._type = type
        self._args = args
        
    @abc.abstractmethod
    def matches(self, wordset): pass

    @property
    def type(self):
        return self._type

    @property
    def args(self):
        return self._args

    def __repr__(self):
        return '{}:{}/{}'.format(self.name, self.path, self.args)

class Track(_Directive):
    
    def __init__(self, name, args):
        super(Track, self).__init__(name, self.__class__.__name__, args)

        # args ~ ("foo", "bar", "lol rofl")

        if not args:
            raise ValueError("Arguments must be a non-empty iterable")

        # must transform args ~ ("foo", "bar", "lol rofl") into 
        # ( ["foo"], ["bar"], ["lol", "rofl"] )
        self._args = [ str(arg).lower().split() for arg in args ]

    def matches(self, wordset):
        # each "arg" in self.args is a list of words to be matched in an AND fashion
        m = Match(path=self.path, 
                  matches=filter(None, (tuple(wordset.intersection(arg)) for arg in self.args)) )
        return [m]



class Locations(_Directive):

    def __init__(self, name, args):
        super(Locations, self).__init__(name, self.__class__.__name__, args)

        if not args:
            raise ValueError("Arguments must be a non-empty iterable")

        if len(args) % 4:
            raise ValueError("Number of coordinates must be a multiple of 4")

        self._args = [ args[i:i+4] for i in range(len(args)//4) ]

    def matches(self, wordset):
        return [] # TODO

class Event(_Node):

    def __init__(self, name):
        super(Event, self).__init__(name)
        self.children = {}
        
    def add(self, *subelements):
        """ Adds subelements (subevent or directive) to this event """
        # must update parent on new subelement
        for subelement in subelements:
            subelement.parent = self
            name = subelement.name
            if name not in self.children:
                self.children[name] = subelement
            else:
                raise ValueError("Subelement '{}' already present in event '{}'".
                        format(name, self.name))

    def matches(self, wordset):
        # the event will match if it has directives among its
        # descendants and they match 
        ch = itertools.chain()
        for sub in self.children.itervalues():
            m = sub.matches(wordset)
            if m:
                ch = itertools.chain(ch, m)
        return ch

    def __str__(self):
        return "Event <{}>".format(self.path)

    def __repr__(self):
        children_reprs = dict( (n, v) for n, v in self.children.iteritems() )
        d = {self.name: children_reprs}
        return pformat(d)

   

#{'root_event': {
#     'evento_1': {'un_track': ['amet', 'd e f'],
#                  'un_locations': [1,2,3,4,5,6,7,8]},
#     'evento_2': {'evento_2_1': 
#                     {'otro_track': 
#                         ['lorem ipsum', 'dolor', 'sit', 'foobar', 'eros', 
#                          'loaoaala', 'lol', 'Fusce sapien ultrices']}}
#     }
#}


# la idea es que en el crawler se pueda ir construyendo este arbol 
# de eventos paulatinamente. Es decir, si en un momento dado hago
# prompt> create track trackBAR foo bar, lol rofl, abc
# prompt> create locations locationFOO 1,2,3,4
# prompt> create event foo with ... <- lista de directivas y/o eventos previamente creados sep. c/ comas
un_track = Track('un_track', ['amet', 'd e f'])
un_locations = Locations('un_locations', [1,2,3,4,5,6,7,8])

evento_1 = Event('evento_1')
evento_1.add(un_track, un_locations)

otro_track = Track('otro_track', ['lorem ipsum', 'dolor', 'sit', 'foobar', 'eros', 
                                  'loaoaala', 'lol', 'Fusce sapien ultrices'])
evento_2_1 = Event('evento_2_1')
evento_2_1.add(otro_track)
evento_2 = Event('evento_2')
evento_2.add(evento_2_1)

tweet = """Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris vel
           tortor sem, et eleifend eros. Fusce viverra nibh sapien, sit amet mattis nisl.
           Maecenas ornare lectus non magna posuere sed ultrices tellus viverra."""

def test(ev, tweet):
    tweet_wordset = set(re.split('\W+', tweet.lower()))
    return dict(ev.matches(tweet_wordset))

print test(evento_1, tweet)
print test(evento_2, tweet)

megaevento = Event("to_p'alla")
megaevento.add(evento_1, evento_2)

print test(megaevento, tweet)

#pprint(test(ev, tweet))
#
#import timeit
#t = timeit.Timer("test(ev, tweet)", "from __main__ import test, ev, tweet")
#secs_per_iter = t.timeit(number=100000)/100000
#print("iters per sec: %.2f" % (1/secs_per_iter))


