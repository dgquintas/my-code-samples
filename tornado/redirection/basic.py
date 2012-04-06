import tornado.ioloop
import tornado.web
import time
class MainHandler(tornado.web.RequestHandler):
    def initialize(self, uno, dos):
        print uno, dos 

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

class AnotherHandler(tornado.web.RequestHandler):
    @tornado.web.addslash
    def get(self):
        self.write("foo")


app = tornado.web.Application([
    (r'/', MainHandler, {'uno':1, 'dos':2}),
    (r'/foo/?', AnotherHandler)
])

if __name__ == '__main__':
    app.listen(8888)
    tornado.ioloop.IOLoop.instance().start()
