#include <emmintrin.h>
#include <stdio.h>

int main(){

  __m128d a,b,c;

  double res[2] __attribute__((aligned(16)));

  a = _mm_set_pd(1,2);
  b = _mm_set_pd(3,4);

  c = _mm_shuffle_pd(a,b, _MM_SHUFFLE2(0,1));

  _mm_store_pd(res, c);

  /* 0 1 */
  printf("%f %f\n", res[0] , res[1]);


  return 0;
}
