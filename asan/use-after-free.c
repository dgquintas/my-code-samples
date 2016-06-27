// compile with:
// {clang,gcc} -fsanitize=address -O1 -fno-omit-frame-pointer -g use-after-free.c
// 
#include <stdlib.h>

int main() {
  char *x = (char*)malloc(10 * sizeof(char*));
  free(x);
  return x[5];
}
