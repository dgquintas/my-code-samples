# calculates the great-circle distance between two points, that is, the
# shortest distance over the earth's surface distance between the points
# (ignoring any hills, of course!).

from __future__ import print_function

def haversine(lat1, long1, lat2, long2):
    from math import sin, cos, atan2, sqrt
    def to_radians(a):
        return a*0.017453292519943295 # a*pi/180
    R = 6371 # Earth's mean radius
    dLat = to_radians(lat2-lat1)
    dLong = to_radians(long2-long1)
    lat1 = to_radians(lat1)
    lat2 = to_radians(lat2)

    a = sin(dLat/2) * sin(dLat/2) + sin(dLong/2) * sin(dLong/2) * \
        cos(lat1) * cos(lat2)
    c = 2 * atan2(sqrt(a), sqrt(1-a))
    return R * c

if __name__ == "__main__":
    d = haversine(40.7486, -73.9864, 43.5481,-5.661)
    print(d)

