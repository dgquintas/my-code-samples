#include <iostream>
#include <stdint.h>

uint64_t addfuncASM(uint64_t a, uint64_t b){
  asm ( "addq %[a], %[b];"
        : "=r" (b)
        : [b] "0"(b), [a] "r" (a)
        : "cc"
      );

  return b;
}

uint64_t addfunc(uint64_t a, uint64_t b){
  b+=a;
  return b;
}


int main(){
  
  unsigned long a,b;

  a = 9796093023208UL;
  b = 549753833388UL;

  addfunc(a,b);
  addfuncASM(a,b);

  return 0;
}

