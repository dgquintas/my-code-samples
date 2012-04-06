#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#define _POSIX_C_SOURCE 200112L

void* functionC();
pthread_mutex_t mutex1;
int  counter = 0;

main()
{
   srand(time(NULL));
   
   pthread_mutexattr_t mutexattr;
   pthread_mutexattr_init(&mutexattr);
   
   // Set the mutex as a recursive mutex
   //causes a recursive lock acq. to return EDEADLOCK "warning"
 //  pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_ERRORCHECK); 
 
   //causes a recursive acq. of the mutex to deadlock
 //  pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_NORMAL); 
 
   pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);

   // create the mutex with the attributes set
   pthread_mutex_init(&mutex1, &mutexattr);

   // After initializing the mutex, the thread attribute can be destroyed
   pthread_mutexattr_destroy(&mutexattr);


   int rc1, rc2;
   pthread_t thread1, thread2;

   /* Create independent threads each of which will execute functionC */

   if( (rc1=pthread_create( &thread1, NULL, &functionC, NULL)) )
   {
      printf("Thread creation failed: %d\n", rc1);
   }

   if( (rc2=pthread_create( &thread2, NULL, &functionC, NULL)) )
   {
      printf("Thread creation failed: %d\n", rc2);
   }

   /* Wait till threads are complete before main continues. Unless we  */
   /* wait we run the risk of executing an exit which will terminate   */
   /* the process and all threads before the threads have completed.   */

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL); 

   exit(0);
}

void *functionC()
{  
    int res;
    if( res= pthread_mutex_lock( &mutex1 ) ){
      printf("%s\n", strerror(res));
      return;
    }
    counter++;
    sleep(rand() % 5);
    printf("Thread 0x%x: Counter value: %d\n",pthread_self(), counter);
    if( counter < 5 ){
      functionC();
    }

    if( res =pthread_mutex_unlock( &mutex1 ) ){
      printf("%s\n", strerror(res));
      return;
    }
   
}
