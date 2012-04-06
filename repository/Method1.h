#ifndef __METHOD1
#define __METHOD1

#include "Method.h"
#include <iostream>

class Method11;



class Method1 : public Method
{
  public:
    typedef Method11 DFL;

};
class Method11 : public Method1
{
  public:
    Method11(){
      std::cout << "LOL" << std::endl;
    }
    int x;
};
#endif
