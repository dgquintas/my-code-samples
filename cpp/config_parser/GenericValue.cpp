#include "GenericValue.h"

std::ostream& operator<<(std::ostream& out, GenericValue gv){
  const std::type_info& thisTypeinfo( gv._getType() );

  if( thisTypeinfo == typeid(int) ){
    out << boost::any_cast<int>(gv._value);
  }
  else if( thisTypeinfo == typeid(double) ){
    out << boost::any_cast<double>(gv._value);
  }
  else if( thisTypeinfo == typeid(bool) ){
    out << boost::any_cast<bool>(gv._value);
  }
  else if( thisTypeinfo == typeid(std::string) ){
    out << "\"" << boost::any_cast<std::string>(gv._value) << "\"" ;
  }
  else{
    assert(false); //FIXME
  }

  return out;
}
