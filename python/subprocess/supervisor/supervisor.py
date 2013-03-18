import subprocess
import threading
import os
import signal

import logging

logging.basicConfig(level=logging.DEBUG)

class CommandRunner(threading.Thread):
    logger = logging.getLogger('CommandRunner')

    def __init__(self, cmd, callback, timeout=None):
        threading.Thread.__init__(self, name='CommandRunner-'+cmd)
        self.cmd = cmd
        self.process = None
        self.timeout = timeout
        self.stdout = None
        self.stderr = None
        self._cb = callback
    
    @property
    def retcode(self):
        return self.process.returncode

    def run(self):
        def target():
            self.logger.info("Thread for command '%s' started", self.cmd)
            self.process = subprocess.Popen(self.cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            self.logger.info("Subprocess '%s' launched with PID '%d'", self.cmd, self.process.pid)
            self.stdout, self.stderr = self.process.communicate() # implicit wait
            self.logger.info("Thread for command '%s' finished", self.cmd)

        thread = threading.Thread(target=target)
        thread.start()

        thread.join(self.timeout) # equivalent to a wait on the subprocess, but with a timeout
        if thread.isAlive():
            self.logger.warn("Subprocess '%s' has timed out after '%d' secs. Killing it", self.cmd, self.timeout)
            if self.process: 
                os.kill(self.process.pid, signal.SIGTERM) # python >=2.6, self.process.terminate()
            thread.join()
        self.logger.info("Command '%s' finished with code '%d'", self.cmd, self.process.returncode)
        self._cb(self)

cmd = "echo 'Process started'; sleep 2; echo 'Process finished'"
def cb(cmdrunner):
    print "I'm the callback, bitches!"
    print "Finished with stdout=%r, stderr=%r and code=%d" % \
            (cmdrunner.stdout, cmdrunner.stderr, cmdrunner.retcode)

# the following instances are run CONCURRENTLY. 
cr = CommandRunner(cmd, cb, timeout=1)
cr.start()
# that will exit with code -15 (ie, negative the number of the killing signal, SIGTERM)

cr = CommandRunner(cmd, cb, timeout=3)
cr.start()
# whereas this will be fine

