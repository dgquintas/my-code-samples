#include <iostream>

using namespace std;

int main(){

  union Type {
    int32_t i;
    float f;
    Type& operator+=(const Type& t){ 
      f += t.f;
      return *this; 
    }
  };

  Type ints, floats;

  ints.i = 123;
  floats.f = 14.88;

  cout << sizeof(Type) << endl;

  cout << ints.i << endl;
  cout << floats.f << endl;

  Type floatRHS;
  floatRHS.f = 1.5;
  floats += floatRHS;

  cout << floats.f << endl;

  return 0;

}


