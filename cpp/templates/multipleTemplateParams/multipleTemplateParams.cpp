#include <iostream>

namespace STR{
template<typename T>
  inline void bar(T t1, T t2) {}
template<typename T, typename U>
  inline void bar2(T t1, U u1) {}
template<typename T>
  inline int get();
};

namespace STR{

template<>
inline void bar<int>(int t1, int t2)
{std::cout << "BEEEEE" << std::endl;}

template<>
inline int get<int>()
 {return 14;}


template<>
inline int get<double>()
 {return 88;}

}


template<typename T>
  void foo(T t){
    STR::bar(t,t);
  }
template<typename T, typename U>
  void foo2(U u, T t){
    STR::bar2(t,u);
  }
template<typename T>
  int get(){
    return STR::get<T>();
  }


int main(){

  float f=1.1;
  int i=2;

  STR::bar(i,i);
  STR::bar(f,f);
  STR::bar2(f,i);
  std::cout << STR::get<int>() << std::endl;
  std::cout << STR::get<double>() << std::endl;

  return 0;
}

