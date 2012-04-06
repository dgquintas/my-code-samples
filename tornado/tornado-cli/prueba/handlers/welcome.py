from handlers.base import BaseHandler

import logging
logger = logging.getLogger('boilerplate.' + __name__)

class WelcomeHandler(BaseHandler):
    def get(self):
        self.render("welcome.html")
