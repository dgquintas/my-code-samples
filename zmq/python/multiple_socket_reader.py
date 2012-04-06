import zmq
import time

context = zmq.Context()

# connect to ventilator
receiver = context.socket(zmq.PULL)
receiver.connect("tcp://localhost:5557")

# connect to weather server
subscriber = context.socket(zmq.SUB)
subscriber.connect("tcp://localhost:5556")
subscriber.setsockopt(zmq.SUBSCRIBE, "10001")

#process msgs from both sockets
#prio goes to task ventilator
while True:

    while True:
        try:
            rc = receiver.recv(zmq.NOBLOCK)
        except zmq.ZMQError:
            break
        # process task here
        pass

    # process any waiting weather updates
    while True:
        try:
            rc = subscriber.recv(zmq.NOBLOCK)
        except zmq.ZMQError:
            break
        #process weather update
        pass

    # no activity, go to sleep
    time.sleep(0.001)

