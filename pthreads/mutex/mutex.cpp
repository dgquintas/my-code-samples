#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *functionC(void*);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  counter = 0;

int main()
{
   int rc1, rc2;
   pthread_t thread1, thread2;

   /* Create independent threads each of which will execute functionC */

   if( (rc1=pthread_create( &thread1, NULL, &functionC, (void*)1)) )
   {
      printf("Thread creation failed: %d\n", rc1);
   }

   if( (rc2=pthread_create( &thread2, NULL, &functionC, (void*)2)) )
   {
      printf("Thread creation failed: %d\n", rc2);
   }

   /* Wait till threads are complete before main continues. Unless we  */
   /* wait we run the risk of executing an exit which will terminate   */
   /* the process and all threads before the threads have completed.   */

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL); 

   pthread_mutex_destroy(&mutex1);
   return 0;
}

void *functionC(void* dummy)
{
   pthread_mutex_lock( &mutex1 );
   counter++;
   printf("Counter value: %d, thread %d\n",counter, (int)dummy);
   if((int)dummy == 1)
     sleep(2);
   pthread_mutex_unlock( &mutex1 );
}
