import requests
import json

user = input('username: ')
pw = input('pw: ')
track = input('track: ')

import sys
cfg = {'verbose': sys.stderr}
r = requests.post('https://stream.twitter.com/1/statuses/filter.json',
    data={'track': track}, auth=(user, pw), config=cfg)

for line in r.iter_lines():
    if line: # filter out keep-alive new lines
        l= line.decode('utf-8')
        if l.startswith('{'):
            print(json.loads(l))
        else:
            print(l)
