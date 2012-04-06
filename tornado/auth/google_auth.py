from __future__ import print_function
import tornado.web
import tornado.auth
import tornado.httpserver
import tornado.ioloop
import json 
from pprint import pprint


class DefaultHandler(tornado.web.RequestHandler):
    def get(self):
        self.write("Nothing to see here\n")

class GoogleHandler(tornado.web.RequestHandler, tornado.auth.GoogleMixin):
    @tornado.web.asynchronous
    def get(self):
        if self.get_argument("openid.mode", None):
            pprint(self.request.arguments)
            self.get_authenticated_user(self.async_callback(self._on_auth))
            return
        self.authenticate_redirect()

    def _on_auth(self, user):
        print("at auth")
        if not user:
            raise tornado.web.HTTPError(500, "Google auth failed")
        # Save the user with, e.g., set_secure_cookie()
        else:
            self.write("YO, whatup bitchesssss " + str(user))
            self.set_status(200)
            self.finish()


import os.path
if __name__ == "__main__":
    app = tornado.web.Application([
        (r"/", DefaultHandler),
        (r"/g", GoogleHandler),
    ])
    cwd = os.path.dirname(os.path.abspath(__file__))
    server = tornado.httpserver.HTTPServer(app, ssl_options=None)
    server.listen(1234)
    tornado.ioloop.IOLoop.instance().set_blocking_log_threshold(0.5)
    tornado.ioloop.IOLoop.instance().start()
