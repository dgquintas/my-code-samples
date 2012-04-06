#include <iostream>
#include <cstdlib>
#include <cassert>
#include <ctime>


using namespace std;

const unsigned int masks[] = { 0x2, 0xc, 0xf0, 0xff00, 0xffff0000 };

int bfffo(unsigned int x){
  int res = 32;
 
  if( x & masks[4] ){
    x >>= 16;
    res -= 16;
  }
  if( x & masks[3] ){
    x >>= 8;
    res -= 8;
  }
  if( x & masks[2] ){
    x >>= 4;
    res -= 4;
  }
  if(x & masks[1] ){
    x >>= 2;
    res -= 2;
  }
  switch(x){
    case 3:
    case 2:
      return res -2 ;
    case 1:
      return res - 1;
    case 0:
      return res ;
  }
}

int bfffoBueno(unsigned int arg1) 
{
  unsigned int ret = 31;
  unsigned int temp; 

  if( (arg1) != (0))  { 
    __asm__ (" bsrl %[_arg1], %[_temp]; " 
        : [_temp] "=r" (temp) 
        : [_arg1] "g" (arg1) 
        ); 
    ret -= temp; 
  }
  else ret++; 

  return ret; 
}

int main(){

  unsigned int x;
 
  srand(time(NULL));

  for(int i=0;i<10000;i++){
    x = (unsigned int)lrand48();
    cout << x << "\t";
    int a = bfffo(x);
    int b = bfffoBueno(x); 
    assert( a == b );
    cout << a << " == " << b << endl;
  }  

  return 0;
}




