#include <iostream>

template<typename T, typename U = double>
class C{
  public:
  void foo();
};

template<typename T, typename U>
void C<T, U>::foo(){ 
  std::cout << typeid(T).name() << std::endl;
  std::cout << typeid(U).name() << std::endl;
}


int main(){

  C<int> c1;
  C<int,float> c2;

  c1.foo();
  c2.foo();

  return 0;

}

