#include <iostream>
#include <x86intrin.h>
#include <inttypes.h>

using namespace std;

int main(){

  uint32_t in1[4] __attribute__((aligned(16))) = 
  {4294967294,2,3,4};
  uint32_t in2[4] __attribute__((aligned(16))) = 
  {2,6,7,8};


  __m128i a = _mm_load_si128((const __m128i*)in1);
  __m128i b = _mm_load_si128((const __m128i*)in2);

  __m128i c = _mm_add_epi32(a,b);

  uint32_t* res = (uint32_t*)&c;

  for(int i=0; i<4;i++){
    cout << res[i] << " ";
  }
  cout << endl;

  return 0;



}
