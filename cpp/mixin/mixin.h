#include <memory>
#include <iostream>

template<typename T>
class Mixin {
  public:
    static T* getInstance(){ 
      T* inst( instance.get() );
      std::cout << "Getting " << inst << std::endl;
      return inst; 
    }
    virtual ~Mixin() { std::cout << "Destroying " << this << std::endl; };
  protected:
    Mixin(){std::cout << "Creating " << this << std::endl; };
    static const std::auto_ptr<T> instance;
};

