#include <string>
#include <iostream>

class A{
  public:
    template<typename T>
      void setName(T* obj){
        std::cout << typeid(*obj).name() << std::endl;
        std::cout << typeid(obj).name() << std::endl;
        std::cout << typeid(T).name() << std::endl;
      };

};
class B {

};
class C : public B{
};


int main(){
  A a;
  B* c = new C();
  
  a.setName(c);

  return 0;
}
