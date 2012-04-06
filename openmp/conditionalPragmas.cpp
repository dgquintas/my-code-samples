#include <omp.h>
#include <iostream>

using namespace std;

int main(){

  if(false){
#pragma omp parallel sections
    {
      cout << omp_get_num_threads() << endl;
    }
  }

  return 0;
}

