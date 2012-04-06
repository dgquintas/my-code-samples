#include <xmmintrin.h>
#include <stdio.h>

int main(){

  __m128 a,b,c;

  float res[4] __attribute__((aligned(16)));

  a = _mm_set_ps(1,2,3,4);
  b = _mm_set_ps(5,6,7,8);

  c = _mm_shuffle_ps(a,b, _MM_SHUFFLE(3,2,1,0));

  _mm_store_ps(res, c);

  /* 4 3 6 5 */
  printf("%f %f %f %f\n", res[0] , res[1], res[2], res[3] );


  return 0;
}
