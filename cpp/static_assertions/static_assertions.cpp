#define STATIC_ASSERT(ex) \
  do { typedef int ai[(ex) ? 1 : -1]; } while(0) 


#include <cassert>

inline static const bool foo(){return false;}

class C{
  public:
    static const int x;

};

const int C::x(false); //if this is put AFTER the
                       // D class destructor, it does NOT work

template<typename T>
class D {
  public:
    ~D(){
      STATIC_ASSERT( T::x );
    }
};



int main(){

  static const int x(1); // it has to be *BOTH* static and const
  STATIC_ASSERT( x );
  static const int y( foo() ); //does NOT work
  STATIC_ASSERT( y );
  //STATIC_ASSERT( sizeof(int) < sizeof(short) );

  D<C> d;
  return 0;
}

