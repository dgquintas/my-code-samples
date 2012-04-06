#include "zhelpers.h"

int main(){

    void* context = zmq_init(1);

    // socket to receive msgs on: the vent
    void* receiver = zmq_socket(context, ZMQ_PULL);
    zmq_connect( receiver, "tcp://localhost:5557");

    // socket to send msgs to: the sink
    void *sender = zmq_socket( context, ZMQ_PUSH);
    zmq_connect( sender, "tcp://localhost:5558");

    int tasks_received = 0;
    //process
    while(1) {
        char* string = s_recv(receiver);

        fflush(stdout);
        printf("%s.", string);

        //do work
        s_sleep(atoi(string));
        free(string);

        //send results to sink
        s_send(sender, "");
        tasks_received++;
    printf("Task %d got %d tasks\n", getpid(), tasks_received);
    }

    zmq_close(receiver);
    zmq_close(sender);
    zmq_term(0);
    return 0;
}
