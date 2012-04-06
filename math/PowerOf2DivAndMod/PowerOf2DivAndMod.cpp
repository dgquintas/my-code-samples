#include <iostream>
#include <stdint.h>

int main(){

  const size_t INT_BITS = 32;
  const size_t LOG2_INT_BITS = 5;
  const size_t DIFF = INT_BITS - LOG2_INT_BITS;

  uint32_t x = 1234;


  std::cout << (x >> LOG2_INT_BITS) << std::endl;
  uint32_t y = x;
  y <<= DIFF;
  y >>= DIFF;
  std::cout << y << std::endl;


  return 0;
}







