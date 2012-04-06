import tornado.ioloop
import tornado.web
import tornado.gen
import time
class MainHandler(tornado.web.RequestHandler):
    @tornado.web.asynchronous
    def get(self):
        self._sleep()
    
    def put(self):
        print self.request
        print self.request.body

    def _sleep(self):
        time.sleep(5) 
        self.write("Hello, world")
        self.set_status(200)
        self.finish()

    def post(self):
        print self.request.body
        time.sleep(0.2)

app = tornado.web.Application([
    (r'/', MainHandler),
])

if __name__ == '__main__':
    app.listen(8888)
    tornado.ioloop.IOLoop.instance().start()
