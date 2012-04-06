#include "some_class.h"
  
  SomeClass::SomeClass()
  : mValA(0), mValB(0)
{}

SomeClass::SomeClass(int a, int b)
  : mValA(a), mValB(b)
{}

void SomeClass::MethodA(){
  mValA *= 2;
}

void SomeClass::MethodB(int a)
{
  mValB *= a;
}

int SomeClass::GetValA(){
  return mValA;
}

std::string SomeClass::bla() const {
  return std::string("paraime");
}



