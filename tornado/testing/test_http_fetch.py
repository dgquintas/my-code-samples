from tornado.testing import AsyncTestCase
from tornado.httpclient import AsyncHTTPClient

# This test uses an asynchronous style similar to most async
# application code.
class MyTestCase(AsyncTestCase):
    def test_http_fetch(self):
        client = AsyncHTTPClient(self.io_loop)
        client.fetch("http://www.tornadoweb.org/", self.handle_fetch)
        self.wait()

    def handle_fetch(self, response):
        # Test contents of response (failures and exceptions here
        # will cause self.wait() to throw an exception and end the
        # test).
        self.assertEqual(response.code, 200)
        self.stop()

# This test uses the argument passing between self.stop and self.wait
# for a simpler, more synchronous style
class MyTestCase2(AsyncTestCase):
    def test_http_fetch(self):
        client = AsyncHTTPClient(self.io_loop)
        client.fetch("http://www.tornadoweb.org/", self.stop)
        response = self.wait()
        # Test contents of response
        self.assertEqual(response.code, 200)


