#include <iostream>

using namespace std;

template<typename T>
void func()
{
  T x = T();
  cout << *x << endl;
}

int main()
{
  int x = int();

  cout << x << endl;

  bool b = bool();

  cout << b << endl;

  func<int*>();

//  int* p = int*(); //but this doesnt work


  return 0;
}
