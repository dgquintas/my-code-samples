# python 3.2

import http.server as server
import re
import pdb

class TokenPrinter(server.BaseHTTPRequestHandler):
    def do_GET(self):
        m = re.search('/foursquare\\?code=([A-Z0-9]+)', self.path)
        self.send_response(200)
        if m:
            code = bytes(m.group(1), 'ascii')
            print(code)
            self.wfile.write(code)
        else:
            self.wfile.write(b"Fail")

        


def run(handler_class):
    server_address = ('',8080)
    httpd = server.HTTPServer(server_address, handler_class)
    httpd.serve_forever()

if __name__ == "__main__":
    run(TokenPrinter)
