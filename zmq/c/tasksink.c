#include "zhelpers.h"

int main(){

    void* context = zmq_init(1);
    void* receiver = zmq_socket(context, ZMQ_PULL);

    zmq_bind(receiver, "tcp://*:5558");

    //wait for start of batch
    char *string = s_recv(receiver);
    free(string);

    //start clock
    int64_t start_time = s_clock();

    //process 100
    int tasks_nbr;
    for( tasks_nbr = 0; tasks_nbr < 100; tasks_nbr++){
        char* string = s_recv(receiver);
        if((tasks_nbr / 10)*10 == tasks_nbr){
            printf(":");
        } else{
            printf(".");
        }
        fflush(stdout);
    }

    printf("Total elapsed time: %d msec\n", 
            (int)(s_clock() - start_time));

    zmq_close(receiver);
    zmq_term(context);
    return 0;
}


    
