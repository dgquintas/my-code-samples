#include <iostream>
#include <omp.h>

int main(){

#pragma omp parallel
  {
      std::cout << "thread " << omp_get_thread_num() << std::endl;
#pragma omp for
      for(int i=0; i<3; i++)
      std::cout << "(for) thread " << omp_get_thread_num() << std::endl;
  }

  return 0;
}
