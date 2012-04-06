from __future__ import print_function
import tornado
import tornado.web
import tornado.auth
import tornado.httpserver
import tornado.ioloop
import json 
import urllib
from pprint import pprint, pformat

class FoursquareMixin(tornado.auth.OAuth2Mixin):
    _OAUTH_ACCESS_TOKEN_URL = 'https://foursquare.com/oauth2/access_token'
    _OAUTH_AUTHORIZE_URL = 'https://foursquare.com/oauth2/authorize'
    
    def get_authenticated_user(self, redirect_uri, client_id, client_secret, 
            code, callback, extra_fields=None):
        http = tornado.httpclient.AsyncHTTPClient()
        args = {
                'redirect_uri': redirect_uri, 
                'code': code,
                'client_id': client_id,
                'client_secret': client_secret,
                'extra_params': { 'grant_type': 'authorization_code', }
               }
        req_url = self._oauth_request_token_url(**args)
        http.fetch( req_url, lambda response: self._on_access_token(callback, response) )

    def _on_access_token(self, callback, response):
        if response.error:
            callback(None)
            return

        body = tornado.escape.json_decode(response.body)
        session = {
                'access_token': body['access_token'],
                }

        self.foursquare_request(
                path='users/self',
                callback=lambda user: self._on_get_user_info(callback, session, user),
                access_token = session['access_token'])
                

    def _on_get_user_info(self, callback, session, user):
        if user is None:
            callback(None)
            return
        user.update({'access_token': session['access_token']})
        callback(user)


    def foursquare_request(self, path, callback, access_token=None, post_args=None, **args):
        url = 'https://api.foursquare.com/v2/' + path
        all_args = {}
        if access_token:
            all_args['oauth_token'] = access_token
            all_args.update(args)
            all_args.update(post_args or {})

        if all_args:
            url += '?' + urllib.urlencode(all_args)

        print("url", url)
        cb = lambda response: self._on_foursquare_request(callback, response)
        http = tornado.httpclient.AsyncHTTPClient()
        if post_args is not None:
            http.fetch(url, method='POST', body=urllib.urlencode(post_args), callback=cb)
        else:
            http.fetch(url, callback=cb)

    def _on_foursquare_request(self, callback, response):
        print("response: ", response)
        if response.error:
            callback(None)
            return
        print("callback", callback)
        callback(tornado.escape.json_decode(response.body))
    

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
        pprint(self.current_user)
        user = self.current_user['response']['user']
        if user['checkins'].get('items') and len(user['checkins']['items']) > 0:
            last_place = user['checkins']['items'][0]
        else:
            last_place = "Sal de casa!!"
        fname = tornado.escape.xhtml_escape(user['firstName'])
        lname = tornado.escape.xhtml_escape(user['lastName'])
        self.write("Yo yo yo wassup " + " ".join([fname,lname]))
        self.write("<br>Ultimo checkin: <br>")
        self.write("<pre>"+pformat(last_place)+"</pre>")
        self.write('<br><a href="/logout">Log out</a>')

class LogoutHandler(BaseHandler):
    def get(self):
        self.clear_cookie('user')
        self.redirect('/')


#class FBRequest(BaseHandler, tornado.auth.FacebookGraphMixin):
#    @tornado.web.authenticated
#    @tornado.web.asynchronous
#    def get(self):
#        self.facebook_request(
#                path='/me/checkins',
#                callback = self._cb, 
#                access_token = self.current_user['access_token'])
#
#    def _cb(self, response_body):
#        pprint( response_body )
#        self.finish()
#
class FourHandler(BaseHandler, FoursquareMixin):
    @tornado.web.asynchronous
    def get(self):
        if self.get_argument('error', False):
            self.write('Error: %s' % self.get_argument('error'))
            self.finish()
        
        elif self.get_argument("code", False): 
            print("got coooode")
            self.get_authenticated_user(
                    redirect_uri = 'https://ptrtovoid.net:8372/foursquare',
                    client_id = self.settings['client_id'],
                    client_secret = self.settings['client_secret'],
                    code = self.get_argument('code'),
                    callback = self._on_login)

        else: # no code: go to auth dialog
            self.authorize_redirect( 
                    redirect_uri='https://ptrtovoid.net:8372/foursquare',
                    client_id = self.settings['client_id'],
                    extra_params = {'response_type': 'code'})
                        

    def _on_login(self, user):
        if not user:
            raise tornado.web.HTTPError(500, "Auth failed")
        user_json = tornado.escape.json_encode(user)
        self.set_secure_cookie('user', user_json)
        self.redirect('/')


import os.path
if __name__ == "__main__":
    app = tornado.web.Application([
        (r"/", MainHandler),
        (r"/foursquare", FourHandler),
#        (r"/fbcheckins", FBRequest),
        (r"/logout", LogoutHandler),
    ], 
    client_id='Z1JIAOJZ2BMUMBOWQDOYO54PUL3JBSKGBIU1XGZ3SWTLCS42',
    client_secret='VXT2WJGTCVNDGHARWC0CRTITNIPLPCO0KEM52SVT32T3HHPD',
    cookie_secret='v3FcZ4chSTip8Kjk3XYHCRJwiWFM40QinXpAgz3y++I=',
    login_url='/foursquare'
    )

    cwd = os.path.dirname(os.path.abspath(__file__))
    ssl_options = {'certfile': os.path.join(cwd, 'ptrtovoid_net.pem') }
    server = tornado.httpserver.HTTPServer(app, ssl_options=ssl_options)
    server.listen(1234)
    tornado.ioloop.IOLoop.instance().set_blocking_log_threshold(0.5)
    tornado.ioloop.IOLoop.instance().start()
