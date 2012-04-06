#ifndef _PROGRAM_H
#define _PROGRAM_H

#include <vector>
#include "code.h"
#include "context.h"

using namespace std;

class Program
{
  public:
    void addCode(Code *);
    int getCount();
    void setCount(int);
    void exec(Context &);
  private:
    int _icount;
    vector<Code*> _code;
};

#endif
