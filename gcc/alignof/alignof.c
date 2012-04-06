#include <stdio.h>
#include <stdint.h>
#include <xmmintrin.h>

int main(){


  printf("%d\n", __alignof__(__m128i));
  return 0;
}
