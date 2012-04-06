#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#define N 50000000

void sieve(uint64_t* const vec, uint64_t n, uint64_t p){
  uint64_t elem;

  for( ; n < N; n+=p ){
    elem = vec[n];
    while( elem % p == 0){
      elem /= p;
    }  
    vec[n] = elem;
  }
}

int main(){
  uint64_t* const vec = (uint64_t*)malloc( sizeof(uint64_t) * N+1);
  uint64_t i;
  for(i =0; i <= N; i++){
    vec[i] = 2*i*i-1;
  }

  uint64_t p;
  for(i=2; i <= N; i++){
    p = vec[i];
    if( p > 1){
      sieve(vec, p+i, p);
      sieve(vec, p-i, p);
    }
  }
  int numPrimes=0;
  for(i=2; i < N; i++){
    if( vec[i] == 2*i*i-1 ){
      numPrimes++;
    }
  }
  printf("%d\n", numPrimes);
  printf("\n");

  return 0;
}
