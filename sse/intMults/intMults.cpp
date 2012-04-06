#include <xmmintrin.h>
#include <cstdio>

using namespace std;

#define NUM_TRIALS 20000000

#define RDTSC(x) asm( "rdtsc;" : "=A"(x) );

int main(){

  __m128i a, b, c;

  int16_t inp_sse1[8] __attribute__((aligned(16))) = { 11,22,33,44,55,66,77,88 };
  int16_t inp_sse2[8] __attribute__((aligned(16))) = { -32, 3246, 432, 31, -44, -123, 321,7890 };
  int16_t out_sse[8] __attribute__((aligned(16)));
  int16_t out[8] __attribute__((aligned(16)));
  int64_t ciclos1,ciclos2;
  float resSin =0.0, resCon=0.0;


  for(int t=0; t < NUM_TRIALS; t++){
    RDTSC(ciclos1);
    for(int i = 0; i < 8; i++) {
      out[i] = inp_sse1[i] * inp_sse2[i];
    }
    RDTSC(ciclos2);
    resSin += (ciclos2-ciclos1)/(float)NUM_TRIALS;
  }
  printf("Sin SSE2: %f ciclos\n", resSin);


  a = _mm_load_si128((__m128i const*)inp_sse1);
  b = _mm_load_si128((__m128i const*)inp_sse2);

  for(int t=0; t < NUM_TRIALS; t++){
    RDTSC(ciclos1);
    c = _mm_mullo_epi16(a,b);
    RDTSC(ciclos2);
    resCon += (ciclos2-ciclos1)/(float)NUM_TRIALS;
  }
  printf("Con SSE2: %f ciclos\n", resCon);

  _mm_store_si128((__m128i*)out_sse, c);

  printf("Speedup = %f\n", resSin/resCon);



  for(int i = 0; i < 8; i++) {
    printf("Result %d: %d   %d\n",i,out_sse[i], out[i]);
  }

  return 0;
}
