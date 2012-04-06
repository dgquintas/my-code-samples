#include <stdint.h>
#include <stdio.h>
void mulNormal(const uint32_t* const a, uint32_t* const b){
  asm ( 
       "movl %[b], %%eax;"
       "mull %[a];"
       "movl %%eax, %[b];"
       "movl %%edx, 4%[b];"

       "movl 8%[b], %%eax;"
       "mull 8%[a];"
       "movl %%eax, 8%[b];"
       "movl %%edx, 12%[b];"


       : 
       : [a] "m" (*a), [b] "m" (*b)
       : "%eax", "%edx", "memory"
      );


  return;
}

int main(){
  uint32_t in1[4] = 
  {4294967295UL,0,3,0};
  uint32_t in2[4]  = 
  {4294967295UL,0,7,0};

  mulNormal(in1, in2);
  int i;
  for(i=0; i < 4; i++)
    printf("%u ", in2[i]);
  printf("\n");

  return 0;
}
