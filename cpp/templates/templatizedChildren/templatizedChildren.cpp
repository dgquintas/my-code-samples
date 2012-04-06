#include <iostream>
#include <vector>

class Base{
  public:
    virtual void foo() const = 0;
};

template<typename T>
class Deriv : public Base {
  public:
    virtual void foo() const {
      std::cout << "blabla" << std::endl;
    }
};
template<typename T>
class Deriv2 : public Base {
  public:
    virtual void foo() const {
      std::cout << "bleble" << std::endl;
    }
};


int main(){

  Deriv<int> d;
  Deriv2<int> d2;

  std::vector<const Base* > v;
  v.push_back(&d);
  v.push_back(&d2);

  for(int i = 0; i < v.size(); i++){
    v[i]->foo();
  }

  return 0;
}
