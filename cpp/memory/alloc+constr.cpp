#include <iostream>

class C{
  public:
    C(int x) : bla(123) { }
    C() : bla(321) { }
    int bla;
};

int main(){

  C vec[2];

  std::cout << vec[0].bla << std::endl;

  return 0;
}
