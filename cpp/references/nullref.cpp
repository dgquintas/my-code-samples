#include <iostream>

class A{
  public:
    A(){
      std::cout << "constructing " << this << std::endl;
    }
    ~A(){
      std::cout << "destroying " << this << std::endl;
    }
};

static A StaticInst = A();

void func(const A& a = StaticInst){
  std::cout << "func" << std::endl;
  return;
}

int main(){

  std::cout << "main pre func()" << std::endl;
  func();
  std::cout << "main post func()" << std::endl;

  A a;

  std::cout << "main pre func(a)" << std::endl;
  func(a);
  std::cout << "main post func(a)" << std::endl;


  return 0;

}
