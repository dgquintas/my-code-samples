#include <iostream>
#include <stdint.h>

using namespace std;

inline bool compare(const uint32_t* const a, 
                    const uint32_t* const b){
  unsigned int res;
  asm ( "movdqu %[b], %%xmm0;"
        "pcmpeqd %[a], %%xmm0;"
        "movd %%xmm0, %[res];"
        : [res] "=g" (res)
        : [a] "m" (*a), [b] "m" (*b)
        : "%xmm0"
      );
  return !(~res);
}

int main(){
  uint32_t a[4] = {1,2,3,6};
  uint32_t b[4] = {1,2,3,4};

  bool ig = compare(a,b);

  cout << ig << endl;

  return 0;
}

