#include <cstdio>

#define INLINE inline

template<typename T>
struct FuncImpl {
  static INLINE int f();
};

template<typename T>
INLINE int f() { FuncImpl<T>::f(); };
/////////////////////////////////////

template<>
  INLINE int FuncImpl<float>::f(){ return 1; };
template<>
  INLINE int FuncImpl<int>::f(){ return 2; };



int main(){

  printf("%d\n", f<float>());
  printf("%d\n", f<int>());

  return 0;
}

