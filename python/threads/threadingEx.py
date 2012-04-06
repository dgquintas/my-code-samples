import threading
import random
from time import sleep

class SharedResource:

    def __init__(self):
        self.evnt = threading.Event()
    
    def get(self, hilo):
        if hilo.x % 2 == 0:
            print "hilo " + `hilo.x` + " waiting"
            self.evnt.wait()
            print "hilo " + `hilo.x` + " awaken"
        elif hilo.x == 123:
            self.evnt.set()
            self.evnt.clear()
            print "hilo " + `hilo.x` + " waking everybody"
        else:
            print "hilo " + `hilo.x` + " passing by"

class Hilo(threading.Thread):

    def __init__(self, x, sr):
        threading.Thread.__init__(self, name = "Hilo"+`x`)
        self.x = x
        self.sr = sr

    def run(self):
        self.sr.get(self)
        if self.x == 96:
          sleep(3)
        print "im thread ", self.getName()
  

def main():
    threads = []
    sr = SharedResource()
    random.seed(0)
    for i in range(10):
        threads.append( Hilo(random.randint(1,200), sr) )

    print "antes:", threading.activeCount()
    for t in threads:
        t.start()

    print "despues: ", threading.activeCount()
    sleep(2)

    sr.evnt.set()
    

    for t in threads:
        print "joining thread ", t.getName()
        t.join()
        print "thread ", t.getName(), " joined"

    print "al final :", threading.activeCount()

#    print threading.enumerate()
        
if __name__ == '__main__':
    main()
