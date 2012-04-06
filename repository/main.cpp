#include "Method1.h"
#include "FuncRep.h"

int main(){
  FuncRep funcs;
  Method *m = new Method1();
  Method1 *m2;
//  funcs.setFunc(m);
  funcs.getFunc(m2); //with m2 holding the default derived class
                     //for the Method1 family of operations

  return 0;
}
