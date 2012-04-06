#include <iostream>

template<typename T>
  class C{
    public:
      C(){};
      C( T data) : _data(data) {}
    private:
      T _data;
  };

namespace Bla{
  template<typename T>
    void f(C<T> c){
      std::cout << typeid(T).name() << std::endl;
    };
};

int main(){

  C<float> cc;
  C<int> ccc;

  Bla::f(cc);
  Bla::f(ccc);

  return 0;

}
      
