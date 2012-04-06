#include "C.h"
#include <iostream>

int main(){

  C<int> c(123);
  C<float> c2(1.23);

  std::cout << c << std::endl;
  std::cout << c2 << std::endl;

  return 0;

}
