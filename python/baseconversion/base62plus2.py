import string
BASE_LIST = string.digits + string.ascii_uppercase + string.ascii_lowercase + '_@'
BASE_DICT = dict((c, i) for i, c in enumerate(BASE_LIST))

def base_decode(string, reverse_base=BASE_DICT):
    length = len(reverse_base)
    ret = 0
    b = 1
    for c in reversed(string):
        ret += b * reverse_base[c]
        b *= length

    return ret

def base_encode(integer, base=BASE_LIST):
    if integer == 0:
        return '0'
    length = len(base)
    ret = ''
    while integer != 0:
        ret = base[integer % length] + ret
        integer //= length

    return ret

if __name__ == "__main__":
    for i in range(100):
        print(i, base_decode(base_encode(i)), base_encode(i))

    import uuid
    id = uuid.uuid4()
    h = id.hex
    enc = base_encode(id.int)
    dec = base_decode(enc)
    print( "{} ({}) -> {} ({})".format(h, len(h), enc, len(enc)))
    print("and back")
    print( "{} -> {}".format(enc, hex(dec)))

    print(base_encode(464634634645724523452624325244532362352342))

    from timeit import Timer
    t1 = Timer('base_encode(464634634645724523452624325244532362352342)', 
            "from __main__ import base_encode")
    print("%.2f usec/pass" % (1000000 * t1.timeit(number=100000)/100000))
    t1 = Timer('base_decode("1LLmFviwaC8duftgcC8ns9RM")', 
            "from __main__ import base_encode, base_decode")
    print("%.2f usec/pass" % (1000000 * t1.timeit(number=100000)/100000))



