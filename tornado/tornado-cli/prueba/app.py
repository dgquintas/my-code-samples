#!/usr/bin/env python

import tornado.httpserver
import tornado.ioloop
import tornado.web
from tornado.options import options

from settings import settings
from urls import url_patterns

class TornadoApp(tornado.web.Application):
    def __init__(self):
        tornado.web.Application.__init__(self, url_patterns, **settings)


def main():
    app = TornadoApp()
    http_server = tornado.httpserver.HTTPServer(app)
    http_server.listen(options.port)
    print 'Tornado server started on port %s' % options.port
    tornado.ioloop.IOLoop.instance().start()

if __name__ == "__main__":
    main()
