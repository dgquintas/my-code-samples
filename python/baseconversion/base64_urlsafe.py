# http://fi.am/entry/urlsafe-base64-encodingdecoding-in-two-lines/
from base64 import urlsafe_b64encode, urlsafe_b64decode

def uri_b64encode(s):
     return urlsafe_b64encode(s).rstrip('=')

def uri_b64decode(s):
     return urlsafe_b64decode(s + '=' * (4 - len(s) % 4))

