#include "pow2.h"
#include <iostream>

  template <int Exponent_S, typename T>
T power(const T& base)
{
  return PowerOf<Exponent_S, T>::eval(base);
}

int main(){

  std::cout <<  PowerOf<5, int>::eval(2)<< std::endl;
  
  return 0;
}
