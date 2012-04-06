#include <cstdio>

int main(){

  int x __attribute((aligned(16))) = 0;

  printf("%d\n", __alignof__(x));




  return 0;
}
