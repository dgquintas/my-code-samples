import itertools, random
import string

ALPHABET = string.digits + string.ascii_uppercase + string.ascii_lowercase + '_@'

def sample_wr_indices(population, k):
    "Chooses k random elements (with replacement) from a population"
    n = len(population)
    _random, _int = random.random, int  # speed hack
    return [_int(_random() * n) for i in itertools.repeat(None, k)]

def sample_wr(population, k):
    "Chooses k random elements (with replacement) from a population"
    n = len(population)
    _random, _int = random.random, int  # speed hack
    return ''.join([ population[_int(_random() * n)] for _ in itertools.repeat(None, k)])

def sample_wr_choice(population, k):
    "Chooses k random elements (with replacement) from a population"
    _choice = random.choice
    return [ _choice(population) for i in itertools.repeat(None, k)]


if __name__ == "__main__":
    from timeit import Timer
    t1 = Timer('sample_wr_indices(ALPHABET, 64)', 
            "from __main__ import ALPHABET, sample_wr_indices")
    print("%.2f usec/pass" % (1000000 * t1.timeit(number=100000)/100000))
    t2 = Timer('sample_wr(ALPHABET, 64)', 
            "from __main__ import ALPHABET, sample_wr")
    print("%.2f usec/pass" % (1000000 * t2.timeit(number=100000)/100000))
    t3 = Timer('sample_wr_choice(ALPHABET, 64)', 
            "from __main__ import ALPHABET, sample_wr_choice")
    print("%.2f usec/pass" % (1000000 * t3.timeit(number=100000)/100000))

