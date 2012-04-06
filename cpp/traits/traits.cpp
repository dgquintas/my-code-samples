#include <cassert>
#include <iostream>

// Example 2(d): Alternative way of requiring
// exactly T* T::Clone() const
//
// T must provide T* T::Clone() const
//
// http://www.gotw.ca/gotw/071.htm
//
//
template<class T, bool COND >
class C
{
  public:
    static bool getX() {
      return T::getX();
    };
    
    // in C's destructor (easier than putting it
    // in every C ctor):
    ~C() {
      assert( ValidateRequirements() );
    }

  private:
    static bool ValidateRequirements()
    {
      T& (T::*test)(const T&) __attribute__ ((__unused__))   = &(T::operator+=) ;
     bool (*test2)() __attribute__ ((__unused__))            = &(T::getX) ;

  //    test; // suppress warnings about unused variables
      // ...
      return true;
    }

};

class Foo : public C<Foo,true> {
  public:
    Foo()
      : C<Foo,true>()
    {}

    static bool getX(){
      return true;
    }

    Foo& operator+=(const Foo& rhs) {
      return *this;
    }
    
};

int main(){
  Foo foo;

  std::cout << foo.getX() << std::endl;

  return 0;
}

