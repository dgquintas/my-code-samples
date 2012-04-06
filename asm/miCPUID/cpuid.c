/* Código quick & dirty para obtencion de información sobre caché via
 * CPUID. 
 *
 * David Garcia Quintas, 2004
 *
 * Basado en lo expuesto en 
 * The IA-32 Intel Architecture Software Developer's Manual,
 * Instruction Set Reference A-M, Order Number 253666;
 * 
 * págs. 3-120 y siguientes. En concreto, tabla 3-16 
 *
 */

#include <stdio.h>

void cpuid(int *a, int *b, int *c, int *d)
{
  asm volatile
    (
     "cpuid \n\t"
     : "=a" (*a), "=b" (*b), "=c" (*c), "=d" (*d)
     : "0" (*a)
    );

  return;
}

int main()
{
  int vecRegs[4]; /* eax, ebx, ecx y edx, resp. */
  int i;

  vecRegs[0] = 2; /* eax contiene inicialmente 2, para obtencion de info sobre tbl y cache */

  cpuid(vecRegs, vecRegs+1, vecRegs+2, vecRegs+3);

  printf("0x%08x 0x%08x 0x%08x 0x%08x\n", 
      vecRegs[0], vecRegs[1], vecRegs[2], vecRegs[3]);

  for(i=0; i<4; i++){
    if( !(vecRegs[i] & 0x80000000) ){ /* los registros con bit 31 a 1 no deben considerarse */
      while( vecRegs[i] ){
        switch( vecRegs[i] & 0xff ){ /* la tabla se indexa por bytes */
          case 0x6:
            printf("1st-level instruction cache: 8 KBytes, 4-way set associative, 32 byte line size\n");
            break;
          case 0x8: 
            printf("1st-level instruction cache: 16 KBytes, 4-way set associative, 32 byte line size\n");
            break;
          case 0xa: 
            printf("1st-level data cache: 8 KBytes, 2-way set associative, 32 byte line size\n");
            break;
          case 0xc: 
            printf("1st-level data cache: 16 KBytes, 4-way set associative, 32 byte line size\n");
            break;
          case 0x22:
            printf("3rd-level cache: 512 KBytes, 4-way set associative, 64 byte line size, 2 lines per sector \n");
            break;
          case 0x23:
            printf("3rd-level cache: 1 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector \n");
            break;
          case 0x25:
            printf("3rd-level cache: 2 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector \n");
            break;
          case 0x29:
            printf("3rd-level cache: 4M Bytes, 8-way set associative, 64 byte line size, 2 lines per sector \n");
            break;
          case 0x2c:
            printf("1st-level data cache: 32K Bytes, 8-way set associative, 64 byte line size \n");
            break;
          case 0x30:
            printf("1st-level instruction cache: 32K Bytes, 8-way set associative, 64 byte line size \n");
            break;
          case 0x40:
            printf("No 2nd-level cache or, if processor contains a valid 2nd-level cache, no 3rd-level cache \n");
            break;
          case 0x41:
            printf("2nd-level cache: 128 KBytes, 4-way set associative, 32 byte line size \n");
            break;
          case 0x42:
            printf("2nd-level cache: 256 KBytes, 4-way set associative, 32 byte line size \n");
            break;
          case 0x43:
            printf("2nd-level cache: 512 KBytes, 4-way set associative, 32 byte line size \n");
            break;
          case 0x44:
            printf("2nd-level cache: 1 MByte, 4-way set associative, 32 byte line size \n");
            break;
          case 0x45:
            printf("2nd-level cache: 2 MByte, 4-way set associative, 32 byte line size \n");
            break;
          case 0x60:
            printf("1st-level data cache: 16 KByte, 8-way set associative, 64 byte line size \n");
            break;
          case 0x66:
            printf("1st-level data cache: 8 KByte, 4-way set associative, 64 byte line size \n");
            break;
          case 0x67:
            printf("1st-level data cache: 16 KByte, 4-way set associative, 64 byte line size \n");
            break;
          case 0x68:
            printf("1st-level data cache: 32 KByte, 4-way set associative, 64 byte line size \n");
            break;
          case 0x78:
            printf("2nd-level cache: 1 MByte, 4-way set associative, 64byte line size \n");
            break;
          case 0x79:
            printf("2nd-level cache: 128 KByte, 8-way set associative, 64 byte line size, 2 lines per sector \n");
            break;
          case 0x7a:
            printf("2nd-level cache: 256 KByte, 8-way set associative, 64 byte line size, 2 lines per sector \n");
            break;
          case 0x7b:
            printf("2nd-level cache: 512 KByte, 8-way set associative, 64 byte line size, 2 lines per sector \n");
            break;
          case 0x7c:
            printf("2nd-level cache: 1 MByte, 8-way set associative, 64 byte line size, 2 lines per sector \n");
            break;
          case 0x7d:
            printf("2nd-level cache: 2 MByte, 8-way set associative, 64byte line size \n");
            break;
          case 0x7f:
            printf("2nd-level cache: 512 KByte, 2-way set associative, 64-byte line size \n");
            break;
          case 0x82:
            printf("2nd-level cache: 256 KByte, 8-way set associative, 32 byte line size \n");
            break;
          case 0x83:
            printf("2nd-level cache: 512 KByte, 8-way set associative, 32 byte line size \n");
            break;
          case 0x84:
            printf("2nd-level cache: 1 MByte, 8-way set associative, 32 byte line size \n");
            break;
          case 0x85:
            printf("2nd-level cache: 2 MByte, 8-way set associative, 32 byte line size \n");
            break;
          case 0x86:
            printf("2nd-level cache: 512 KByte, 4-way set associative, 64 byte line size \n");
            break;
          case 0x87:
            printf("2nd-level cache: 1 MByte, 8-way set associative, 64 byte line size \n");
            break;

        }
        vecRegs[i] >>= 8; /* siguiente byte */
      }
    }
  }


  return 0;
}
