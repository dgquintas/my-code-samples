#include <omp.h>
#include <iostream>

using namespace std;

int main(){

  int i;
  int v[99];

#pragma omp parallel \
  private(i) shared(v)
  {

    cout << "Thread " << omp_get_thread_num() << endl;
#pragma omp for nowait
    for(i=0; i < 99; i++){
      v[i] = i;
    }
  }

  for(i=0; i < 99; i++){
    cout << v[i] << " " ;
  }

  return 0;
}

