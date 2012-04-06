#ifndef __METHOD2
#define __METHOD2

#include "Method.h"
class Method2 : public Method
{
  public:
    virtual void insert(FuncRep* const fr){
      fr->_set(this);
    };

};

#endif
