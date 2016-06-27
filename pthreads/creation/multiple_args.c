#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

struct thread_data {
    int thread_id;
    int sum;
    char *message;
};

/* Replicate data per thread */
struct thread_data thread_data_array[NUM_THREADS];

void* PrintHello(void* threadarg) {
    struct thread_data *my_data = (struct thread_data*) threadarg;
    printf("Hello world from thread #%d! Msg: %s\n", my_data->thread_id,
           my_data->message);
    /*
     *void pthread_exit(void *retval);
     */
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    pthread_t threads[NUM_THREADS];
    long t;
    int rc;
    for (t = 0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %ld\n", t);
        thread_data_array[t].thread_id = t;
        thread_data_array[t].sum = 333;
        thread_data_array[t].message = (char*) malloc(32);
        snprintf(thread_data_array[t].message, 32, "LOL %ld", t);
        /*
         *int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
         *                   void *(*start_routine) (void *), void *arg);
         */
        if ((rc = pthread_create(&threads[t], NULL, PrintHello,
                                 (void*)&thread_data_array[t]))) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for (t = 0; t < NUM_THREADS; t++) {
        /*
         *int pthread_join(pthread_t thread, void **retval);
         */
        pthread_join(threads[t], NULL);
        free(thread_data_array[t].message);
    }

    return 0;
}
