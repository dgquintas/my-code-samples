import tornado.httpserver
import tornado.ioloop
import tornado.web
import os

class MainHandler(tornado.web.RequestHandler):
    def get(self):
        self.write("Hello, world")


if __name__ == "__main__":
    application = tornado.web.Application([
        (r"/", MainHandler),
    ])

    cwd = os.path.dirname(os.path.abspath(__file__))
    ssl_options = {'certfile': os.path.join(cwd, 'public.pem'),
                   'keyfile':  os.path.join(cwd, 'private.key') }

    server = tornado.httpserver.HTTPServer(application, ssl_options=ssl_options)
    server.listen(8888)
    tornado.ioloop.IOLoop.instance().start()
