import tornado.ioloop
import tornado.web
import tornado.httpclient as httpclient

ahttpclient = httpclient.AsyncHTTPClient()
httpclient = httpclient.HTTPClient()

import sys

class AsyncHandler(tornado.web.RequestHandler):

    @tornado.web.asynchronous
    def get(self, port):
        def on_response(response):
            self.write("Got: %s" % response.body)
            self.finish()

        ahttpclient.fetch('http://localhost:%s/'%port, callback=on_response)

class SyncHandler(tornado.web.RequestHandler):
    def get(self, port):
        self.write(httpclient.fetch('http://localhost:%s/'%port).body)


    
app = tornado.web.Application([
    (r'/async/(\d+)', AsyncHandler),
    (r'/sync/(\d+)', SyncHandler),
])

if __name__ == '__main__':
    app.listen(8888)
    tornado.ioloop.IOLoop.instance().start()
