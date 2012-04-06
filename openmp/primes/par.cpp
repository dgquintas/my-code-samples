#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

int main(){
  const int max = 1000000; 

  vector<int> primes(80000);
  primes[0]=(2);


  int i;
  int k = 1;

#pragma omp parallel \
  private(i) shared(primes,k)
  {
  cout << "TH: " << omp_get_thread_num() << endl;
#pragma omp for nowait
    for(i = 3; i < max; i+=2 ){
      bool prime = true;
      for(int j = 3; j <= (i>>2); j += 2 ){
        if( ((i % j) == 0) ){
          prime = false;
          break;
        }
      }
      if(prime){
        primes[k++]=i;
      }
    }

    cout << "fin TH: " << omp_get_thread_num() << endl;
  }

//  sort(primes.begin(), primes.begin()+k);
//  for(int l=0; l<k;l++){
//    cout << primes[l] << " " ;
//  }
//  cout << endl;

  return 0;
}





