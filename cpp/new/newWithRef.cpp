#include <iostream>

using namespace std;

class C{
  public:
    C(int x) 
      : _x(x) {};

    C(const C& src)
      : _x(src._x) {};

    ~C() {};

    int get() const {return _x; } 

    C& operator=(const C& src){
      if( &src != this ){
        this->C::~C();
        new (this) C(src); //placement operator: stroustrup 10.4.11
        return *this;
      }
    }
  private:
    const int _x;
  
  friend ostream& operator<<(const ostream& out, const C& c) ;
};

ostream& operator<<(ostream& out, const C& c) {
  out << c.get();
  return out;
}


int main(){
  C c(314);
  C d(271);

  C& ref(c);
  cout << "ref (pre) = " << ref << endl;
  ref = d;
  cout << "ref (post) = " << ref << endl;
  cout << "c = " << c << endl;
  cout << "d = " << d << endl;

  return 0;
}

