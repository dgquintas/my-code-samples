#include <iostream>
#include <emmintrin.h>

using namespace std;

inline void mul(const uint32_t* const a, uint32_t* const b){

  asm volatile (
       "movdqu %[a], %%xmm0;"
       "movdqu %[b], %%xmm1;"
       "pmuludq %%xmm0, %%xmm1;"
       "movdqu %%xmm1, %[b];"
      : 
      : [a] "m" (*a), [b] "m" (*b)
      : "%xmm0","%xmm1", "memory"
      ); 


}


int main(){

  uint32_t in1[4] = 
  {4294967295UL,0,3,0};
  uint32_t in2[4]  = 
  {4294967295UL,0,7,0};


//  __m128i a = _mm_load_si128((const __m128i*)in1);
//  __m128i b = _mm_load_si128((const __m128i*)in2);
//
//  __m128i c =_mm_mul_epu32(a,b);
//
//  uint32_t* res = (uint32_t*)&c;
//
//  for(int i=0; i<4;i++){
//    cout << res[i] << " ";
//  }
//  cout << endl;

  mul(in1, in2);

  for(int i=0; i<4;i++){
    cout << in2[i] << " ";
  }
  cout << endl;


  return 0;



}
