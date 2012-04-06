#include <iostream>
#include <string>

int main(){

  std::string res("[");
  uint32_t eax, edx, ecx;
  eax = 1;

  asm ( "cpuid;"
      : "=d"(edx), "=c"(ecx)
      : "a"(eax)
      );
 
  if( edx & (1L << 23) ){
    res += "\"MMX\"" ;
  }
  
  if( edx & (1L << 25) ){
    res += ", \"SSE\"" ;
  }

  if( edx & (1L << 26) ){
    res += ", \"SSE2\"" ;
  }
  
  if( ecx & (1L) ){
    res += ", \"SSE3\"" ;
  }

  if( ecx & (1L << 9) ){
    res += ", \"SSSE3\"" ;
  } 

  

  res += "]";

  std::cout << res << std::endl;
  
  return 0;
}
