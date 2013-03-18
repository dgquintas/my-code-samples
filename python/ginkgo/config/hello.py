from ginkgo import Service, Setting

from hello_mod import AnotherService

class HelloWorld(Service):
    message = Setting("message", default="Hello World",
        help="Message to print out while running")
    tralara = Setting("uno.dos.tralara")

    def do_start(self):
        self.spawn(self.message_forever)

    def message_forever(self):
        while True:
            print self.tralara
            self.async.sleep(1)

class SubService(Service):
    lol = Setting("lol", default="XD", help="risas")
    
    def do_start(self):
        pass


