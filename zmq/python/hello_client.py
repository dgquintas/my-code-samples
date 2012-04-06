import zmq
import time

context = zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

for i in range(1,10):
    socket.send("foo"+str(i))
    reply = socket.recv()
    print "Received reply: ", reply



