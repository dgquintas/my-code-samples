from ginkgo import Setting
from base import BaseService

class AnotherService(BaseService):
    deriv = Setting("deriv", default="deriv", help="deriv")
    
    def do_start(self):
        pass


