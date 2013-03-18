# cf. http://stackoverflow.com/a/402471

import logging

logging.basicConfig()

def logged(cls):
    cls.logger = logging.getLogger("{0}.{1}".format(__name__, cls.__name__))
    return cls

@logged
class Foo(object):

    def __init__(self):
        self.logger.warn("foo")

f = Foo()
