#include <iostream>

class A{
  public:
    A() : i(123) {};
    int i;
};

class B{
  public:
    B() : d(1.234) {};
    double d;
};


int main(){

  A* a = new A();
  B* b = new B();

  std::cout << a->i << std::endl;
  std::cout << b->d << std::endl;

  B* ba = static_cast<B*>(a);

  return 0;
}
  


