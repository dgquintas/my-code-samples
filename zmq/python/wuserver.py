import zmq
import random

context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind("tcp://*:5556")

while True:
    zipcode = random.randrange(1,100000)
    temp = random.randrange(1,215) - 80
    relhumid = random.randrange(1,50) + 10

    socket.send(bytes("%d %d %d" % (zipcode, temp, relhumid),'ascii'))
    

