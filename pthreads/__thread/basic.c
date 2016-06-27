#include <stdio.h>
#include <pthread.h>

#define UNUSED __attribute__((unused))

void iterate() {
    /*static int i = 0; UNSAFE! global */
    static __thread int i = 0; /* Now the compiler makes sure that every thread
                                  accesses its own copy of "i" */
    i++;
    printf("Thread id: 0x%lx, i=%d\n", pthread_self(), i);
}

void* thread_func(void* data UNUSED) {
    iterate();
    return (void*)0;
}

int main() {
    pthread_t tid[5];
    int i = 0;

    for (i = 0; i < 5; i++) pthread_create(&tid[i], NULL, thread_func, NULL);
    for (i = 0; i < 5; i++) pthread_join(tid[i], NULL);
}
