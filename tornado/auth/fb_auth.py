from __future__ import print_function
import tornado.web
import tornado.auth
import tornado.httpserver
import tornado.ioloop
import json 
from pprint import pprint, pformat

class BaseHandler(tornado.web.RequestHandler):
    def get_current_user(self):
        user_json = self.get_secure_cookie('user')
        if not user_json:
            return None
        else:
            return tornado.escape.json_decode(user_json)


class MainHandler(BaseHandler):
    @tornado.web.authenticated
    def get(self):
        print("current user", pformat(self.current_user))
        name = tornado.escape.xhtml_escape(self.current_user['name'])
        self.write("Yo yo yo wassup " + name)
        self.write('<br><a href="/logout">Log out</a>')

class LogoutHandler(BaseHandler):
    def get(self):
        self.clear_cookie('user')
        self.redirect('/')


class FBRequest(BaseHandler, tornado.auth.FacebookGraphMixin):
    @tornado.web.authenticated
    @tornado.web.asynchronous
    def get(self):
        self.facebook_request(
                path='/me/checkins',
                callback = self._cb, 
                access_token = self.current_user['access_token'])

    def _cb(self, response_body):
        pprint( response_body )
        self.finish()


class FBHandler(BaseHandler, tornado.auth.FacebookGraphMixin):
    @tornado.web.asynchronous
    def get(self):
        if self.get_argument('error', False):
            reason = self.get_argument('error_reason')
            descr = self.get_argument('error_description')
            self.write('Error: %s, %s' % (reason,descr))
            self.finish()
        
        elif self.get_argument("code", False): 
            self.get_authenticated_user(
                    redirect_uri = 'https://ptrtovoid.net:8372/fblogin',
                    client_id = self.settings['facebook_client_id'],
                    client_secret = self.settings['facebook_client_secret'],
                    code = self.get_argument('code'),
                    callback = self._on_login)

        else: # no code: go to FB's auth dialog
            self.authorize_redirect( 
                    redirect_uri='https://ptrtovoid.net:8372/fblogin',
                    client_id = self.settings['facebook_client_id'],
                    extra_params = {'scope': "user_checkins,friends_checkins,user_photos"})
                        

    def _on_login(self, user):
        if not user:
            raise tornado.web.HTTPError(500, "Auth failed")
        user_json = tornado.escape.json_encode(user)
        self.set_secure_cookie('user', user_json)
        pprint(user_json)
        self.redirect('/')


import os.path
if __name__ == "__main__":
    app = tornado.web.Application([
        (r"/", MainHandler),
        (r"/fblogin", FBHandler),
        (r"/fbcheckins", FBRequest),
        (r"/logout", LogoutHandler),
    ], 
    facebook_client_id='204425046289380',
    facebook_client_secret='d7e2f60bb8a0983aa95b2f36bd83f930',
    cookie_secret='v3FcZ4chSTip8Kjk3XYHCRJwiWFM40QinXpAgz3y++I=',
    login_url='/fblogin'
    )

    cwd = os.path.dirname(os.path.abspath(__file__))
    ssl_options = {'certfile': os.path.join(cwd, 'ptrtovoid_net.pem') }
    server = tornado.httpserver.HTTPServer(app, ssl_options=ssl_options)
    server.listen(1234)
    tornado.ioloop.IOLoop.instance().set_blocking_log_threshold(0.5)
    tornado.ioloop.IOLoop.instance().start()
