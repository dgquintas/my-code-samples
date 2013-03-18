from __future__ import print_function
import hmac
import hashlib
import time
import base64

X = 30
key = base64.b32decode("wa2oatxr5y65iugt".upper().encode())
print(hashlib.sha1(key).hexdigest())

def HOTP(K, C, Digit=6):
    # HOTP(K,C) = Truncate(HMAC-SHA-1(K,C))
    def DT(h):
        offset = h[-1] & 0xf
        p = int.from_bytes(h[offset:offset+4], byteorder="big")
        return p & 0x7fffffff
    HS = hmac.new(K, C, digestmod=hashlib.sha1).digest()
    # HS is a 20-byte (160 bit) hash
    Snum = DT(HS)
    return Snum % (10**Digit)

def TOTP(K):
    T = int(time.time()) // X
    return HOTP(K, T.to_bytes(8, "big"))

#print(TOTP(key))

while True:
    t = int(time.time())
    print(t, t % X)
    T = int(time.time()) // X
    print(T)
    print(TOTP(key))
    print()
    time.sleep(1)




