#include "zhelpers.h"

int main(){
    void *context = zmq_init(1);

    // socket to send msgs on
    void* sender = zmq_socket(context, ZMQ_PUSH);
    zmq_bind(sender, "tcp://*:5557");

    // socket to send start of batch msg on
    void *sink = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sink, "tcp://localhost:5558");

    printf("Press enter wieh workers are ready");
    getchar();
    printf("Sending tasks to workers...\n");

    //first msg is "0" and kickstarts the sink
//    s_send(sink, "0");

    srandom((unsigned) time(NULL) );
    
    //send 100 tasks
    int task_nbr;
    int total_msec = 0;

    for(task_nbr = 0; task_nbr < 100; task_nbr++){
        int workload;
        workload = randof(100)+1;
        total_msec += workload;
        char string[10];
        sprintf(string, "%d", workload);
        s_send(sender, string);
    }
    printf("Total expected cost: %d msec\n", total_msec);
    sleep(1);

    zmq_close(sink);
    zmq_close(sender);
    zmq_term(context);
    return 0;
}


