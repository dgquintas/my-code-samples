#include <string>
#include <iomanip>

#include "ConfigSet.h"

ConfigSet::ConfigSet()
  : std::map<std::string,GenericValue>()    
{}
ConfigSet::ConfigSet(const ConfigSet& other)
  : std::map<std::string,GenericValue>(other)    
{}

ConfigSet& ConfigSet::operator=(const ConfigSet& other){
  std::map<std::string,GenericValue>::operator=(other);
  return *this;
}

GenericValue& ConfigSet::operator[](const std::string& k){
  if( this->find( k ) == this->end() ){
    std::cerr << "Attempting to access a non-existant config line key: " << k << std::endl;
    exit(-1);
  }
  return std::map<std::string,GenericValue>::operator[](k);
}

std::ostream& operator<<(std::ostream& out, ConfigSet cs){
  ConfigSet::iterator it;
  for( it = cs.begin(); it != cs.end(); it++ ){
    out << it->first << " = " << std::showpoint << it->second << '\n';
  }

  return out;
}


