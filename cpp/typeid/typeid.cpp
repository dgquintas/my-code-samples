// typeid, polymorphic class
#include <iostream>
#include <typeinfo>
#include <exception>
#include <string>
using namespace std;

//XXX: ojo!!! la clase base ha de tener algo virtual
class CBase { 
  public:
    CBase()
    : _name( typeid(this).name() )
    {}

    virtual string getName(){ return _name; } 

  private:
    const string _name;
};
class CDerived : public CBase {};
class CDerivedDerived : public CDerived{};

void func(CBase *a){
    cout << "a (in func) is: " << typeid(a).name() << '\n';
    cout << "*a (in func) is: " << typeid(*a).name() << '\n';
}

int main () {
  try {
    CBase* a = new CBase;
    CBase* b = new CDerived;
    CDerived* c = new CDerivedDerived;
    cout << "a is: " << typeid(a).name() << '\n';
    cout << "b is: " << typeid(b).name() << '\n';
    cout << "c is: " << typeid(c).name() << '\n';
    cout << "*a is: " << typeid(*a).name() << '\n';
    cout << "*b is: " << typeid(*b).name() << '\n';
    cout << "*c is: " << typeid(*c).name() << '\n';
    func(c);
    cout << endl << endl;
    cout << "a is: " << a->getName() << '\n';
    cout << "b is: " << b->getName() << '\n';
    cout << "c is: " << c->getName() << '\n';


    cout << "float is: " << typeid(float).name() << '\n';
    cout << "double is: " << typeid(double).name() << '\n';
    cout << "int is: " << typeid(int).name() << '\n';
    cout << "int16_t is: " << typeid(int16_t).name() << '\n';

    func(b);
  } catch (exception& e) { cout << "Exception: " << e.what() << endl; }
  return 0;
}
