#include <xmmintrin.h>
#include <cstdio>

using namespace std;

#define RDTSC(x) asm( "rdtsc;" : "=A"(x) );

int main(){

  __m128 a, b, c;

  float inp_sse1[8] __attribute__((aligned(16))) = { 11,22,33,44 };
  float inp_sse2[8] __attribute__((aligned(16))) = { -32, 3246, 432, 31 };
  float out_sse[8] __attribute__((aligned(16)));
  float out[8] __attribute__((aligned(16)));
  int64_t ciclos1,ciclos2;

  RDTSC(ciclos1);
  for(int i = 0; i < 4; i++) {
    out[i] = inp_sse1[i] * inp_sse2[i];
  }
  RDTSC(ciclos2);
  printf("%lld ciclos\n", ciclos2-ciclos1);


  RDTSC(ciclos1);
  a = _mm_load_ps(inp_sse1);
  b = _mm_load_ps(inp_sse2);
  c = _mm_mul_ps(a,b);
  RDTSC(ciclos2);
  printf("%lld ciclos\n", ciclos2-ciclos1);

  _mm_store_ps(out_sse, c);

  for(int i = 0; i < 4; i++) {
    printf("Result %d: %f   %f\n",i,out_sse[i], out[i]);
  }

  return 0;
}
