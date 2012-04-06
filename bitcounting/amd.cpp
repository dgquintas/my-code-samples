#include <iostream>

inline bool isPrime(int x) {
  switch(x){
    case 2:
    case 3:
    case 5:
    case 7:
    case 11:
    case 13:
    case 17:
    case 19:
    case 23:
    case 29:
    case 31:
      return true;
    default:
      return false;
  }
}

inline int bitCount(uint32_t v){
  v = v - ((v >> 1) & 0x55555555);                    // reuse input as temporary
  v = (v & 0x33333333) + ((v >> 2) & 0x33333333);     // temp
  return ((v + (v >> 4) & 0xF0F0F0F) * 0x1010101) >> 24; // count
}


int naiveNumPrimeBits(uint32_t ini, uint32_t end){
  int c = 0;
  for(uint32_t i = ini; i <= end; i++){
    if( isPrime(bitCount(i)) ){
      c++;
    }
  }
  return c;
}

int optzNumPrimeBits(uint32_t ini, uint32_t end){
  int c = 0;
  int prev = 0;
  for(uint32_t i = ini; i <= end; ){
    int bc = bitCount(i);
    if( bc == 1){
      std::cout << i << " -> " << c-prev << std::endl;
      prev = c;
    }

    if( i & 0x1 ){ //odd
      if( isPrime(bc) ){
        c++;
      }
      i++;
    }
    else{ //even
      if( bc == 1 ){
        c++;
        i+=2; 
      }
      else if( bc == 2 ){
        c+=2;
        i+=2;
      }
      else if( bc & 0x1 ){
        if( isPrime(bc) ){
          c++;
        }
        i+=2;
      }
      else{
        i++;
      }
    }
  }
  return c;
}





int main(){
  uint32_t n,m;
  std::cin >> n >> m;
//  std::cout << naiveNumPrimeBits(n,m) << std::endl;
  std::cout << optzNumPrimeBits(n,m) << std::endl;

  return 0;
}
