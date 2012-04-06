#include <iostream>
#include <cmath>
#include <omp.h>

int main(){

  const int chunk_size = ceil(10.0/omp_get_max_threads());
#pragma omp parallel for schedule(static, chunk_size)
  for(int i = 0;  i< 10; i ++) {
      std::cout << "thread " << omp_get_thread_num() << std::endl;
  }

  return 0;
}
