#include <iostream>

template<typename T>
class TypeRef;

template<>
class TypeRef<int>{
  public:
  typedef long long int FOO;
};
template<>
class TypeRef<float>{
  public:
  typedef char FOO;
};



int main(){

  std::cout << sizeof(TypeRef<int>::FOO) << std::endl;
  std::cout << sizeof(TypeRef<float>::FOO) << std::endl;
  std::cout << sizeof(TypeRef<double>::FOO) << std::endl;

  return 0;
}
