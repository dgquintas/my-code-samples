#include "head.h"

void Foo::bar(){
  return;
}

int Foo::lol(){
  this->bar();
  return 123;
}
