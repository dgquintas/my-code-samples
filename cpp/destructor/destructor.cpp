#include <iostream>
#include <boost/pool/object_pool.hpp>

class Foo{
  public:
  Foo(){ std::cout << "construyendo FOO: " << this << std::endl; }
  ~Foo() { std::cout << "FOO being destructed: " << this << std::endl; }
};

class Bar{
  public:
    Bar(){
      std::cout << "construyendo BAR: " << this << std::endl;
    }
    ~Bar(){
      std::cout << "DEStruyendo BAR: " << this << std::endl;
    }

  private:
    Foo foo;
};

int main(){
  
    boost::object_pool<Bar> pool;

    for(int i=0; i < 5; i++)
      Bar* bar = pool.construct();
  

  std::cout << "eeend" << std::endl;

  return 0;
}

