#include <iostream>

using namespace std;

template<typename T>
class BaseBase {
  public:
    void foo(){ cout << "ROFL" << endl;}
    virtual T pure(T x) = 0;
  protected:
    BaseBase(){};
};

template<typename T>
class Base{};

class Bla{};

template<>
class Base<float> : public BaseBase<float>
{
  public:
    //XXX: if the following method is declared, is "shadows" the inherited one,
    //even if they dont have the same signature :?
   // virtual float pure(Bla y){ cout << "pure" << endl;}
    virtual void bar();
};

void Base<float>::bar(){
  cout << "LOL" << endl;
}


class Derived1 : public Base<float> {
  public:
    Derived1(){};
    virtual float pure(float x) { cout << "DERIV 1" << endl;}
};
//
//class Derived2 : public BaseBase<float> {
//  public:
//    void foo() { cout << "DERIV 2" << endl; }
//    Derived2(){};
//};




int main(){
//  Base<int> b;
//  Base<double> b2;
  Base<float>* d = new Derived1();

//  Derived1 d1;
//  Derived2 d2;

//  b.foo();
//  b2.foo();
  d->foo();
  d->bar();
  d->pure(1.1);
  
//  d1.pure();
//  d2.foo();
//  d2.bar();

  return 0;
}
