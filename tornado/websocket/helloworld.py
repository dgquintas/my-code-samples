import tornado.websocket
import tornado.web
import tornado.ioloop
import tornado.httpserver

class WSHandler(tornado.websocket.WebSocketHandler):
    def open(self):
        print 'new connection'
        self.write_message("Hello world")

    def on_message(self, message):
        print 'msg received: %s' % message
        self.close()

    def on_close(self):
        print 'conn closed'


app = tornado.web.Application([
    (r'/ws', WSHandler),
    ])

if __name__ == "__main__":
    http_server = tornado.httpserver.HTTPServer(app)
    http_server.listen(8888)
    tornado.ioloop.IOLoop.instance().start()
    
