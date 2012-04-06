#include "gnral.h"
#include <iostream>

void funcA(){
  Gnral::getInstance()->setX(321);
}
void funcB(){
  int x = Gnral::getInstance()->getX();
  std::cout << x << std::endl;
}

int main(){
  Gnral* gnral = Gnral::getInstance();
  std::cout << gnral->getX() << std::endl;

  funcA();
  funcB();


  return 0;
}
