#include <iostream>

using namespace std;

class Foo
{
  public:
    int func() const { return 1; }
};

class Bar : public Foo
{
  public:
    int func() const { return 2; }
};


int main(){
  Bar bar;

  const Foo& foo(bar);

  cout << foo.func() << endl;
  cout << bar.func() << endl;

  return 0;
}

