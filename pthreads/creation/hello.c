#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void* PrintHello(void* threadid) {
    long tid;
    tid = (long)threadid;
    printf("Hello world from thread #%ld!\n", tid);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    pthread_t threads[NUM_THREADS];
    long t;
    int rc;
    for (t = 0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %ld\n", t);
        /*
         *int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
         *                   void *(*start_routine) (void *), void *arg);
         */
        if ((rc = pthread_create(&threads[t], NULL, PrintHello, (void*)t))) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    /* Don't die before the children threads */
    /*
     *void pthread_exit(void *retval);
     */
    pthread_exit(NULL);
}
