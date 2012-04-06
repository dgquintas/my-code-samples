import sys
import zmq

context = zmq.Context()
socket = context.socket(zmq.SUB)

print "Collecting updates from weather server..."
socket.connect("tcp://localhost:5556")

# subscribe to zipcode
filter = sys.argv[1] if len(sys.argv) > 1 else "10001"
socket.setsockopt(zmq.SUBSCRIBE, filter)

# get 5 updates
total_temp = 0 
for update_nbr in range(5):
    print update_nbr
    string = socket.recv()
    zipcode, temp, relhumid = string.split()
    total_temp += int(temp)

print "Avg. temp for zipcode '%s' was %dF" % (filter, total_temp/update_nbr)
