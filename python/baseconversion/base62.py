import string
BASE_LIST = string.digits + string.ascii_uppercase + string.ascii_lowercase + '_@'
BASE_DICT = dict((c, i) for i, c in enumerate(BASE_LIST))

import array

def bytes_to_int(s):
    arr = array.array('B') #unsigned char
    arr.frombytes(s)
    base_bits = arr.itemsize << 3
    res = 0
    for d in arr:
        res <<= base_bits
        res += d
    return res

def int_to_bytes(i):
    arr = array.array('B') #unsigned char
    base_bits = arr.itemsize << 3
    mask = (1 << base_bits )-1
    while i:
        arr.append(i & mask)
        i >>= base_bits
    arr.reverse()
    return arr.tobytes()

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
    import json
    s = json.dumps([[2012,5,8,1,35,52],'twitter','522433936'])
    i = bytes_to_int(s.encode())
    print(i)
    print(base_encode(i))
    print(int_to_str(i))

    import zlib
    i = bytes_to_int(zlib.compress(s.encode()))
    print(i)
    print(base_encode(i))


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



