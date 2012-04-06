var http = require('http');
var util = require('util');

var server = http.createServer(function (request, response) {
        response.writeHead(200, {'Content-Type': 'text/plain'});
        response.end('Hello world!\n');
        console.log("Request for: %s",request.url)
        }).listen(1234);

server.on('connection', function (socket) {
    console.log("Connection made from %s:%d", socket.remoteAddress, socket.remotePort);
});

server.on('close', function () {
    console.log("Connection closed");
});

setInterval(function () {
    console.log(util.inspect(process.memoryUsage(), 
            false, null, true));
}, 1000);


console.log('Server version %s running on http://127.0.0.1:1234/', process.version);
