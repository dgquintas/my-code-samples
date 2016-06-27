import tornado.ioloop
import tornado.web

class MainHandler(tornado.web.RequestHandler):
    def initialize(self, data):
        self._data = data

    def get(self, arg):
        self.write("Hello, world: {} {}".
                   format(self._data, arg))

application = tornado.web.Application([
    (r"/(\w*)", MainHandler, {'data': 1}),
])

if __name__ == "__main__":
    application.listen(8888)
    tornado.ioloop.IOLoop.instance().start()
