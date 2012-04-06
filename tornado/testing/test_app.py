from tornado.testing import AsyncHTTPTestCase
from tornado.httpclient import AsyncHTTPClient
from tornado.web import Application, RequestHandler

import pdb

class Handler(RequestHandler):
    def get(self):
        self.write('foobar')

class MyHTTPTest(AsyncHTTPTestCase):
    def get_app(self):
        return Application([('/', Handler)])

    def test_homepage(self):
        # The following two lines are equivalent to
        #   response = self.fetch('/')
        # but are shown in full here to demonstrate explicit use
        # of self.stop and self.wait.
        self.http_client.fetch(self.get_url('/'), self.stop)
        response = self.wait()
        # test contents of response
        self.assertEqual(response.body, b'foobar')
