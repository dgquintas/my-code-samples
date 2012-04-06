#ifndef __FUNCREP
#define __FUNCREP

#include "Method.h"
#include <map>
#include <string>
#include <typeinfo>
#include <iostream>
#include <cassert>

using namespace std;


class FuncRep{
  public:
    void setFunc(Method* const m){
      //acquire lock
      _set(m);
      //release lock
      return;
    }

    template<typename T>
      void getFunc(T* m) {
        //acquire lock
        _get<T>(m);
        //release lock
        return;
      }


  private:
     void _set(Method* const m){
       const string name(typeid(*m).name());
       _methods[name] = m;
     };


     template<typename T>
       void _get(T* m) {
         const string name(typeid(T).name());
         if( _methods.find(name) == _methods.end() ){
           T* newInstance = new typename T::DFL();
           _methods[name] = newInstance;
           m = newInstance;
         }
         else{
           m = dynamic_cast<T*>(_methods[name]);
           assert(m != 0);
         }
       }


   map<string, Method* > _methods;
};

#endif
