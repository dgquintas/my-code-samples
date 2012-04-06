#include <iostream>

using namespace std;

class Foo
{
  public:
    Foo()
    {
      _union.x = 123;
    }

    template<typename T>
      void get(T& bla){
        bla = *(reinterpret_cast<T*>(&_union));
      }

    template<typename T>
      void set(const T& bla){
         *((T*)&_union) = bla;
      }




  private:
    union {
    int x;
    char c;
    } _union;
};

int main(){

  Foo foo;

  int x;
  char c;

  foo.get(x);
  foo.get(c);

  cout << x << endl;
  cout << c << endl;

  foo.set('x');
 
  foo.get(x);
  foo.get(c);

  cout << x << endl;
  cout << c << endl;

  return 0;
}
