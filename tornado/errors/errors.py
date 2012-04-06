import tornado.ioloop
import tornado.web
import time
import traceback

class MainHandler(tornado.web.RequestHandler):
    def get(self):
        self.write("yo wassup")
        #raise Exception("woops")
        self.send_error(408)

    def write_error(self, code, **kwargs):
        trace = kwargs.get('exc_info')
        tb = traceback.format_exception(*trace) if trace else None
        tbstr = '<br/>'.join(tb) if tb else None
        self.render('500.html', code=code, tb=tbstr)
    
app = tornado.web.Application([(r'/', MainHandler), ], debug=True)

if __name__ == '__main__':
    app.listen(8888)
    tornado.ioloop.IOLoop.instance().start()
