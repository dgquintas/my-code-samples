import tornado.ioloop
import tornado.web
import time
import logging

logging.basicConfig()
logger = logging.getLogger(__name__)

class MainHandler(tornado.web.RequestHandler):

    def load_json(self):
        """Load JSON from the request body and store them in
        self.request.arguments, like Tornado does by default for POSTed form
        parameters.

        If JSON cannot be decoded, raises an HTTPError with status 400.
        """
        try:
            self.request.arguments = json.loads(self.request.body)
        except ValueError:
            msg = "Could not decode JSON: %s" % self.request.body
            logger.debug(msg)
            raise tornado.web.HTTPError(400, msg)

    def get_json_argument(self, name, default=None):
        """Find and return the argument with key 'name' from JSON request data.
        Similar to Tornado's get_argument() method.
        """
        if default is None:
            default = self._ARG_DEFAULT
        if not self.request.arguments:
            self.load_json()
        if name not in self.request.arguments:
            if default is self._ARG_DEFAULT:
                msg = "Missing argument '%s'" % name
                logger.debug(msg)
                raise tornado.web.HTTPError(400, msg)
            logger.debug("Returning default argument %s, as we couldn't find "
                    "'%s' in %s" % (default, name, self.request.arguments))
            return default
        arg = self.request.arguments[name]
        logger.debug("Found '%s': %s in JSON arguments" % (name, arg))
        return arg


    def post(self):
        print self.request
        print self.request.arguments
        print self.request.body
        print "get_arguments('foo'): ", self.get_arguments("foo")
        print "get_json_argument('json'): ", self.get_json_argument('json')
        self.write("WIN")

    def put(self):
        print self.request
        print self.request.arguments
        print self.request.body

app = tornado.web.Application([
    (r'/', MainHandler),
])

if __name__ == '__main__':
    app.listen(8888)
    tornado.ioloop.IOLoop.instance().start()
