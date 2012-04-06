#include <xmmintrin.h>
#include <cstdio>
#include <cassert>
#include <ctime>

using namespace std;

#define NUM_TRIALS 20000000
#define ELEMS_PER_VECTOR 16

#define RDTSC(x) asm( "rdtsc;" : "=A"(x) );

int main(){

  __m128i a, b, c;

  bool inp_sse1[ELEMS_PER_VECTOR] __attribute__((aligned(ELEMS_PER_VECTOR))) 
    = { 11,22,33,44,55,66,77,88,11,22,33,44,55,66,77,88 };
  bool inp_sse2[ELEMS_PER_VECTOR] __attribute__((aligned(ELEMS_PER_VECTOR))) = 
  { -32, 36, 43, 31, -44, -123, 31,78, -32, 46, 42, 31, -44, -123, 21,70 };
  bool out_sse[ELEMS_PER_VECTOR] __attribute__((aligned(ELEMS_PER_VECTOR)));
  bool out[ELEMS_PER_VECTOR] __attribute__((aligned(ELEMS_PER_VECTOR)));
  int64_t ciclos1,ciclos2;
  float resSin =0.0, resCon=0.0;

#if 1
  resSin = clock();
  for(int t=0; t < NUM_TRIALS; t++){
//    RDTSC(ciclos1);
    for(int i = 0; i < ELEMS_PER_VECTOR; i++) {
      out[i] = inp_sse1[i] & inp_sse2[i];
    }
//    RDTSC(ciclos2);
//    resSin += (ciclos2-ciclos1)/(float)NUM_TRIALS;
  }
  resSin = clock() - resSin;
  resSin /= CLOCKS_PER_SEC;

  printf("Sin SSE2: %f ciclos\n", resSin);


#endif
  a = _mm_load_si128((__m128i const*)inp_sse1);
  b = _mm_load_si128((__m128i const*)inp_sse2);
  resCon = clock();
  for(int t=0; t < NUM_TRIALS; t++){
//    RDTSC(ciclos1);
    c = _mm_and_si128(a,b);
    _mm_store_si128((__m128i*)out_sse, c);
//    RDTSC(ciclos2);
//    resCon += (ciclos2-ciclos1)/(float)NUM_TRIALS;
  }
  resCon = clock() - resCon;
  resCon /= CLOCKS_PER_SEC;
  printf("Con SSE2: %f ciclos\n", resCon);

#if 1 
  printf("Speedup = %f\n", resSin/resCon);



  for(int i = 0; i < ELEMS_PER_VECTOR; i++) {
    assert(out_sse[i] == out[i]);
  }

#endif
  return 0;
}
