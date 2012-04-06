#include <iostream>
#include <string>

template<int I>
class Foo{
  public:
    int getParam(){ return I; };
};

template<std::string* NAME>
class Bar{
  public:
    std::string getParam(){ return *NAME; };
};


int main(){

  Foo<123> foo;
  const std::string x("LOL");
  const std::string* const y = &x;
  Bar<y> bar;

  std::cout << foo.getParam() << std::endl;
  std::cout << bar.getParam() << std::endl;

  return 0;
}
