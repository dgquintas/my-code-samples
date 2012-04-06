#include <iostream>

class C{
  public:
    C(int x)
      : _x(x) {}
    C(const C& src)
      : _x(src._x){}

    int getX() const{
      return _x;
    }

    static C STATIC;
    static C ini(){ 
      C c;
      c._x = 321;
      return c;
    };

  private:
    C(){};
    int _x;
};


C C::STATIC( C::ini() );

int main(){

  std::cout << C::STATIC.getX() << std::endl;
  C c(99);
  std::cout << c.getX() << std::endl;
  std::cout << c.STATIC.getX() << std::endl;


  return 0;
}

