#include "head.h"
#include <cstdio>
#include <iostream>

int globalFunc(){
  return 321;
}

void stats(){}

int main(){

  Foo foo;

  std::cout << foo.lol() << std::endl;

  globalFunc();

  stats();
  return 0;
}

