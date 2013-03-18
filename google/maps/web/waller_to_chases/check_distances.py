from __future__ import print_function
import requests.async
import json

def get_url(src, dst, mode='walking'):
    PATTERN = ('http://maps.googleapis.com/maps/api/distancematrix/json?'
               'origins={}&destinations={}'
               '&mode={}&sensor=false')
    return PATTERN.format(src, dst, mode)

def parse_response(response):
    # ret: [distance, src, dst]
    d = json.loads(response.text)
    src = d['origin_addresses'][0]
    dst = d['destination_addresses'][0]
    distance = d['rows'][0]['elements'][0]['distance']['value'] 
    distance_txt = d['rows'][0]['elements'][0]['distance']['text'] 
    time = d['rows'][0]['elements'][0]['duration']['value'] 
    time_txt = d['rows'][0]['elements'][0]['duration']['text'] 
    return [[distance, distance_txt], [time, time_txt], src, dst]



if __name__ == '__main__':
    import sys
    src = sys.argv[1]
    fname = sys.argv[2]
    urls = []
    with open(fname, 'r') as f:
        urls = [ get_url(src, line.strip(), 'biking') for line in f ]

    reqs = [requests.async.get(url) for url in urls]
    resps = requests.async.map(reqs, size=4)

    parsed = [ parse_response(resp) for resp in resps ]
    for p in sorted(parsed):
        print(p)





