#include <iostream>
class Base{
  public:
  void f(){
    g();
  }
  virtual void g(){
    std::cout << "base" << std::endl;
  }
};

class Deriv : public Base {
  public:
    virtual void g(){
      std::cout << "deriv" << std::endl;
    }

};

int main(){
  Deriv d;

  d.f();

  return 0;

}

