#include <xmmintrin.h>
#include <cstdio>

using namespace std;


int main(){

  __m128i a, b, c;
  __m128 af,bf,cf;
  __m128d d;

  printf("%d\n", sizeof(a)/sizeof(int16_t) );
  printf("%d\n", sizeof(af)/sizeof(float) );
  printf("%d\n", sizeof(d)/sizeof(double) );

  int32_t inp_sse1[4] __attribute__((aligned(16))) = { 22, 33, 11, 22 };
  int32_t inp_sse2[4] __attribute__((aligned(16))) = { -12, 23, 31, -44 };
  int32_t out_sse[4] __attribute__((aligned(16)));
  float out_ssef[4] __attribute__((aligned(16)));

  a = _mm_load_si128((__m128i const*)inp_sse1);
  af = _mm_cvtepi32_ps(a);

  b = _mm_load_si128((__m128i const*)inp_sse2);
  bf = _mm_cvtepi32_ps(b);

  cf = _mm_mul_ps(af,bf);
  c = _mm_cvtps_epi32(cf);

  _mm_store_ps(out_ssef,cf);
  _mm_store_si128((__m128i*)out_sse, c);

  for(int i = 0; i < 4; i++) {
    printf("Result %d: %d\n",i,out_sse[i]);
  }

  printf("\n");

  for(int i = 0; i < 4; i++) {
    printf("Result %d: %.2f\n",i,out_ssef[i]);
  }


  return 0;
}
