#include <cstdio>

int main(){

  typedef struct { float f[4]; } __attribute__ ((aligned (16))) __m128;

  printf("%d\n", __alignof__(__m128));

  return 0;
}
