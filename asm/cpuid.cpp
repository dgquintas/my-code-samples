#include <iostream>
#include <string>
#include <cstring>

#include <stdint.h>

void cpuid(uint32_t &eax, uint32_t &ebx, uint32_t &ecx, uint32_t &edx){
  asm ( "cpuid;"
      : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
      : "0"(eax),"1"(ebx), "2"(ecx), "3"(edx)
      );
}


int main(){

  std::string res("[");
  enum { EAX = 0, EBX, ECX, EDX };
  uint32_t regs[4];
  regs[EAX] = 1;
  cpuid( regs[EAX], regs[EBX], regs[ECX], regs[EDX]);
 
  if( regs[EDX] & (1L << 23) ){
    res += "\"MMX\"" ;
  }
  
  if( regs[EDX] & (1L << 25) ){
    res += ", \"SSE\"" ;
  }

  if( regs[EDX] & (1L << 26) ){
    res += ", \"SSE2\"" ;
  }
  
  if( regs[ECX] & (1L) ){
    res += ", \"SSE3\"" ;
  }

  if( regs[ECX] & (1L << 9) ){
    res += ", \"SSSE3\"" ;
  } 
 
  regs[EAX] = 0x80000001;
  cpuid( regs[EAX], regs[EBX], regs[ECX], regs[EDX]);
  if( regs[EDX] & (1L << 29) ){
    std::cout << "x86-64 supported" << std::endl;
  }
  else{
    std::cout << "x86-64 *not* supported" << std::endl;
  }
 

  res += "]";

  std::cout << res << std::endl;

  static char* BRAND_TABLE[24] = {
    /* 00H */ "This processor does not support the brand identification feature",
    /* 01H */ "Intel(R) Celeron(R) processor",
    /* 02H */ "Intel(R) Pentium(R) III processor",
    /* 03H */ "Intel(R) Pentium(R) III Xeon(R) processor / Intel(R) Celeron(R) processor",
    /* 04H */ "Intel(R) Pentium(R) III processor",
    /* 05H */ "",
    /* 06H */ "Mobile Intel(R) Pentium(R) III processor-M",
    /* 07H */ "Mobile Intel(R) Celeron(R) processor1",
    /* 08H */ "Intel(R) Pentium(R) 4 processor",
    /* 09H */ "Intel(R) Pentium(R) 4 processor",
    /* 0AH */ "Intel(R) Celeron(R) processor1",
    /* 0BH */ "Intel(R) Xeon(R) processor / Intel(R) Xeon(R) processor MP",
    /* 0CH */ "Intel(R) Xeon(R) processor MP",
    /* 0DH */ "",
    /* 0EH */ "Mobile Intel(R) Pentium(R) 4 processor-M / Intel(R) Xeon(R) processor",
    /* 0FH */ "Mobile Intel(R) Celeron(R) processor",
    /* 10H */ "",
    /* 11H */ "Mobile Genuine Intel(R) processor",
    /* 12H */ "Intel(R) Celeron(R) M processor",
    /* 13H */ "Mobile Intel(R) Celeron(R) processor",
    /* 14H */ "Intel(R) Celeron(R) processor",
    /* 15H */ "Mobile Genuine Intel(R) processor",
    /* 16H */ "Intel(R) Pentium(R) M processor",
    /* 17H */ "Mobile Intel(R) Celeron(R) processor"
  };

  regs[EAX] = 0x80000000;
  cpuid( regs[EAX], regs[EBX], regs[ECX], regs[EDX]);
  if( regs[EAX] & 0x80000000 ){

    char brand[48];

    regs[EAX] = 0x80000002;
    cpuid( regs[EAX], regs[EBX], regs[ECX], regs[EDX]);
    memcpy(&brand[0], regs, sizeof(uint32_t)*4);

    regs[EAX] = 0x80000003;
    cpuid( regs[EAX], regs[EBX], regs[ECX], regs[EDX]);
    memcpy(&brand[16], regs, sizeof(uint32_t)*4);

    regs[EAX] = 0x80000004;
    cpuid( regs[EAX], regs[EBX], regs[ECX], regs[EDX]);
    memcpy(&brand[32], regs, sizeof(uint32_t)*4);


    std::cout << brand << std::endl;
  }
  else{
    regs[EAX] = 1;
    cpuid( regs[EAX], regs[EBX], regs[ECX], regs[EDX]);

    const short idx = regs[EBX] & 0xff;
    std::cout << BRAND_TABLE[ idx ] << std::endl;
  }


  
  return 0;
}
