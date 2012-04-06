from __future__ import print_function
import pycurl 
import getpass
import json
import pdb 
import cassandra
import logging
from pprint import pprint

logging.basicConfig(level=logging.DEBUG)

class Client(object):

    def __init__(self, url, user, pw):
        self._CURL = pycurl.Curl()
        self._CURL.setopt(pycurl.URL, url)
        self._CURL.setopt(pycurl.USERPWD, '%s:%s' % (user, pw))
        self._CURL.setopt(pycurl.WRITEFUNCTION, self.onreceive_cb)

        self._buffer = ''

    def connect(self):
        self._CURL.perform()

    def onreceive_cb(self, data):
        # three possible scenarios:
        # 1) the whole JSON message is received within data. This is signed by having a single
        # \r\n at the end of data.
        # 2) only part of the JSON message is received. 
        #       2.1) Only initial part. This won't have any \r\n anywhere
        #       2.2) Second part. Will have one \r\n
        # 3) more than one JSON message is received. The first part is most likely what's left
        # from a previous unfinished message. The rest of the message will fall within on of the
        # two previous scenarios.
        #
        # in the end, always append to the buffer up to the first \r\n. Reset the buffer to whatever
        # is left in data after that \r\n (possibly an empty string).
        # Process the buffer if it ends with \r\n
        
        cutoff = data.find('\r\n')
        if cutoff < 0: # \r\n not found
            cutoff = len(data)
        else:
            cutoff += len('\r\n')

        self._buffer += data[:cutoff]
        data = data[cutoff:] 

        while self._buffer.endswith('\r\n') and self._buffer.strip():
            body = json.loads(self._buffer)
            user = body.get('user')
            if user and user['name']: 
                logging.info("Adding to USERS: %s, %s, %s, %s",  user['name'], user['id'], user['location'], user['lang'] )
                cassandra.insert_user( user['name'], user['id'], user['location'], user['lang'] )
            text = body.get('text')
            if text and user['name']:
                logging.info("Adding to TWEETS: %s, %s, %s, %s", user['name'], text, body['geo'], body['created_at'] )
                cassandra.insert_tweet( user['name'], text, str(body['geo']), body['created_at'] )
            self._buffer = data
            
if __name__ == '__main__':
    try:
        input = raw_input
    except:
        pass
    USER = input('User: ')
    PASS = getpass.getpass('Pw: ')
    
    URL = 'https://stream.twitter.com/1/statuses/sample.json'

    c = Client(URL, USER, PASS)
    c.connect()

