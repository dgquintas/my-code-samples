import gevent
from gevent import queue 
from gevent import socket
from gevent import monkey
monkey.patch_all()

import time
import json
from pprint import pprint as pp
import oauth2 as oauthlib

import urllib2

APP_ID = '238wxCPGoMwEmn1HVe7bw'
APP_SECRET = 'Xksa5nSKQPLgTXjdUTaEfgSnR6OwOyvpBtbyShXBU4'

token_info = {
    "oauth_token_secret" : "An7jVS0bYAOF8ylB0UuxuUjsXefbZJQYSAnFbVx4",
    "oauth_token" : "25830968-3ysbPFf0IJtnJwaeWTcsF3lK0hJ2Lyleg1Viakxgj",
}

def readtwitter(twitter_params, q):
    oauthlib_consumer = oauthlib.Consumer(APP_ID, APP_SECRET)
    token = oauthlib.Token(token_info['oauth_token'],
                           token_info['oauth_token_secret'])

    #url = 'https://stream.twitter.com/1/statuses/filter.json'
    url = 'https://stream.twitter.com/1/statuses/sample.json'

    signature_method = oauthlib.SignatureMethod_HMAC_SHA1()

    req_params = params = {
            'oauth_version': "1.0",
            'oauth_nonce': oauthlib.generate_nonce(),
            'oauth_timestamp': int(time.time()),
            'oauth_token': token.key,
            'oauth_consumer_key': oauthlib_consumer.key,
            }
    req_params.update(twitter_params)

    req = oauthlib.Request.from_consumer_and_token(
            oauthlib_consumer,
            token=token,
            http_url=str(url),
            http_method='POST')

    req = oauthlib.Request(method="POST", url=str(url), parameters=req_params)
    req.sign_request(signature_method, oauthlib_consumer, token)

    print url
    print req.to_postdata()
    f = urllib2.urlopen(url, req.to_postdata())

    buf = f.read(1024)
    #assert buf.startswith('{')
    print "XXXXXXXXXXXXXXXXXX", buf[:20]
    while buf:
        sep = buf.find('\r\n')
        if sep >=0:
            # found the separator. Chop from beginning of
            # buffer up to this point, process it and empty 
            # buffer
            msg = buf[:sep]
            msgdict = json.loads(msg)
            try:
                print msgdict['user']['name'], msgdict['text']
                q.put(msgdict['text'])
            except KeyError:
                pass
            buf = buf[sep+2:]
        buf += f.read(1024)



def foo():
    while True:
       print "FOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"
       gevent.sleep(1)

def poster(q):
    s= gevent.socket.create_connection(('localhost', 8000))
    for item in q:
        s.sendall(bytearray(item, encoding='utf-8'))

q = queue.Queue()
jobs = [
        #gevent.spawn(readtwitter, {'track': 'spain'}),
        gevent.spawn(readtwitter, {}, q),
        gevent.spawn(foo),
        gevent.spawn(poster, q)]
gevent.joinall(jobs)
