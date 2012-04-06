import tornado.ioloop
import tornado.web
import time
class MainHandler(tornado.web.RequestHandler):
    def get(self):
        self.write("Starting to write, slowly...")
        time.sleep(5) 
        self.write("and we are back and done")
    
app = tornado.web.Application([
    (r'/', MainHandler),
])

import sys
if __name__ == '__main__':
    app.listen(int(sys.argv[1]))
    tornado.ioloop.IOLoop.instance().start()
