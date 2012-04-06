// dynamic_cast
#include <iostream>
#include <exception>
using namespace std;

class CBase { 
  virtual void dummy() {} 
};

class CDerived: public CBase { 
  int a; 
};

template<typename SRC, typename DST>
bool isInstanceOf(){
  SRC *dummy = new SRC;
  const bool res(dynamic_cast<DST*>(dummy));
  delete dummy;
  return res;
}


int main () {
    CBase * pba = new CDerived;
    CBase * pbb = new CBase;
    CDerived * pd;

    cout << isInstanceOf<CDerived, CBase>() << endl;
    cout << isInstanceOf<CBase, CDerived>() << endl;

    pd = dynamic_cast<CDerived*>(pba);
    if (pd==0) cout << "Null pointer on first type-cast" << endl;

    pd = dynamic_cast<CDerived*>(pbb);
    if (pd==0) cout << "Null pointer on second type-cast" << endl;

    // now casting references. dynamic_cast will throw std::bad_cast if
    // sth goes wrong
  CDerived d;
  CBase b;

  try {
      dynamic_cast<CBase&>(d);
  } catch (exception& e) {
      cout << "Exception in derived -> base references: " << e.what() << endl;
  }
  try {
      dynamic_cast<CDerived&>(b);
  } catch (exception& e) {
      cout << "Exception in base -> derived references: " << e.what() << endl;
  }

  // what's the address of a cast from automatic var to pointer?
  pba = dynamic_cast<CBase*>(&d);
  cout << "Addr of reference, &d: " << &d << endl;
  cout << "Addr pointer after dynamic cast to CBase* of &d: " << pba << endl;
  // it's the same! which means shit would hit the fan if we were to use 
  // pba after "d" is automatically destroyed
  return 0;
}
