#include <omp.h>
#include <iostream>

int main(){
  std::cout << omp_get_num_procs() << std::endl;
  int i;
  std::cout << omp_get_max_threads() << std::endl;
#pragma omp parallel for
  for( int i = 0; i < 1; i++){
    std::cout << omp_get_num_threads() << std::endl;
  }

  return 0;
}
