#ifndef __GENERICVALUE_H
#define __GENERICVALUE_H

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <boost/any.hpp>

class GenericValue
{
  public:

    template<typename T>
      void getValue(T& output){
        try {
          output = boost::any_cast<T>(_value);
        }
        catch( boost::bad_any_cast ){
          std::cerr << 
            "ERROR: Attempted to convert a " 
            << _value.type().name() 
            << " into " 
            << typeid(T).name() 
            << std::endl;
          exit(-1);
        }
      }

    template<typename T>
      void setValue(const T& input){
        _value = input;
      }


  friend std::ostream& operator<<(std::ostream&, GenericValue);


  private:
    boost::any _value;
    const std::type_info& _getType() const { return _value.type(); }


};



#endif

