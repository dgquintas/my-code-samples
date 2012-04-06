import zmq
import time

context = zmq.Context()

# connect to ventilator
receiver = context.socket(zmq.PULL)
receiver.connect("tcp://localhost:5557")

# connect to weather server
subscriber = context.socket(zmq.SUB)
subscriber.connect("tcp://localhost:5556")
#subscriber.setsockopt(zmq.SUBSCRIBE, b"oo")

#initialize poll set
poller = zmq.Poller()
poller.register(receiver, zmq.POLLIN)
poller.register(subscriber, zmq.POLLIN)

#process msgs from both sockets
while True:
    socks = dict(poller.poll())

    if receiver in socks and socks[receiver] == zmq.POLLIN:
        message = receiver.recv()
        #process task
        print("processing task", message)
    

    if subscriber in socks and socks[subscriber] == zmq.POLLIN:
        message = subscriber.recv()
        #process weather update
        print("weatheeeeeeeer")


