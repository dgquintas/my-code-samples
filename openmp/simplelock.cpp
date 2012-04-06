#include <stdio.h>
#include <omp.h>
#include <unistd.h>
void skip(int i) { printf("Thread %d skipping\n", i); }
void work(int i) { printf("Thread %d working\n", i); sleep(1);}
int main()
{
  omp_lock_t lck;
  int id;
  omp_init_lock(&lck);
#pragma omp parallel shared(lck) private(id)
  {
    id = omp_get_thread_num();
    omp_set_lock(&lck);
    /* only one thread at a time can execute this printf */
    printf("My thread id is %d.\n", id);
    omp_unset_lock(&lck);
//    while (! omp_test_lock(&lck)) {
//      skip(id); /* we do not yet have the lock,
//                   so we must do something else */
//    }
    omp_set_lock(&lck);
    work(id); /* we now have the lock
                 and can do the work */
    omp_unset_lock(&lck);
  }
  omp_destroy_lock(&lck);
  return 0;
}
