from ginkgo import Service, Setting

class BaseService(Service):
    base = Setting("base", default="base", help="base")
    
    def do_start(self):
        pass


