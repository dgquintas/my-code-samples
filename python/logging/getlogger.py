import logging
logging.basicConfig()

l1 = logging.getLogger(__name__)
print "l1's name:", l1.name


class C(object):

    l2 = logging.getLogger(__name__)

    def __init__(self):
        self.l2.warn("boo!")

c = C()

