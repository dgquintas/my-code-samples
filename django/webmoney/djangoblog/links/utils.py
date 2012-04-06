import urllib 
import time
import dateutil.parser
import dateutil.tz
import xml.etree.cElementTree as xml_parser
from django.utils.encoding import smart_unicode

from djangoblog.links.models import Link

class DeliciousClient(object):
    interval = 0

    def __init__(self, username, password):
        self.username, self.password = username, password
    
    def fetch(self, **params):
        delta = time.time() - DeliciousClient.interval
        if delta < 2:
            time.sleep(2 - delta)
        DeliciousClient.interval = time.time()
        url = 'https://%s:%s@api.del.icio.us/v1/posts/recent' % (self.username, self.password)
        return self.fetch_xml(url)
    
    def fetch_xml(self, url):
        u = urllib.FancyURLopener(None)
        usock = u.open(url)
        rawdata = usock.read()
        usock.close()
        return xml_parser.fromstring(rawdata)

        
    def __getattr__(self, method):
        return DeliciousClient(self.username, self.password, '%s/%s' % (self.method, method))
        
    def __repr__(self):
        return "<DeliciousClient>"
        

def create_link(data):
    for post in data.findall('post'):
        info = dict((k, smart_unicode(post.get(k))) for k in post.keys())
        b, created = Link.objects.get_or_create(
            url = info['href'],
            description = info['extended'],
            tags = info.get('tag', ''),
            date = parsedate(info['time']),
            title = info['description']
        )


def parsedate(s):
	dt = dateutil.parser.parse(s)
	if dt.tzinfo:
	    dt = dt.astimezone(dateutil.tz.tzlocal()).replace(tzinfo=None)
	return dt

