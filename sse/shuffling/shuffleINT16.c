#include <emmintrin.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define RDTSC(x) asm( "rdtsc;" : "=A"(x)  );

int main(){
  srand( time(NULL));
  __m128i a;
  uint64_t t1,t2;

  int16_t vec[8]  __attribute__((aligned(16))); 
  int i;
  for(i = 0 ; i < 8 ; i ++){
    vec[i] = rand() % 100;
//    printf(" %d ", vec[i]);
  }
  printf("\n");

  int16_t res[8] __attribute__((aligned(16)));
//  a = _mm_load_epi16(12,23,3,42,51,63,74,81);
  a = _mm_load_si128((__m128i const*)vec);
  RDTSC(t1);
  a = _mm_add_epi16(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1,0,0,0)) );
  a = _mm_add_epi16(a, _mm_shuffle_epi32( a, _MM_SHUFFLE(2,2,2,2) ));
  a = _mm_add_epi16(a, _mm_shufflehi_epi16( a, _MM_SHUFFLE(2,2,2,2) ));
  const int16_t sum = _mm_extract_epi16(a, 7);
  RDTSC(t2);

  printf("Res = %d\n", sum);
  printf("Tpo = %lld\n", t2-t1);

  int16_t sum2 = 0;

  RDTSC(t1);
  for(i=0; i<8; i++){
    sum2 += vec[i];
  }
  RDTSC(t2);
 
  printf("Res = %d\n", sum2);
  printf("Tpo = %lld\n", t2-t1);

  return 0;
}
