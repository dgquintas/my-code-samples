#include <vector>
#include <iostream>
#include <cassert>

class Wrapper{

  virtual void foo() {}
};

template<typename T>
class SubWrapper : public Wrapper
{
  public:
  virtual void foo() {}
  T getIdem(){ return _data; };

  private:
  T _data;
};

void SubOnly(SubWrapper<int> x){
  x.getIdem();
};


int main(){

  std::vector< Wrapper* > v;

  SubWrapper<int> a;
  SubWrapper<float> b;

  v.push_back(&a);
  v.push_back(&b);

  std::cout << typeid(a).name() << std::endl;
  std::cout << typeid(*(v[0])).name() << std::endl;
  
  v[0]->getIdem();

  SubWrapper<int>* ap;
  ap = dynamic_cast<SubWrapper<int>* >(v[0]);
  assert(ap);
  ap->getIdem();
  SubOnly(*ap);

  return 0;

}
