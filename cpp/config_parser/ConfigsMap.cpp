#include "ConfigsMap.h"

ConfigsMap::ConfigsMap()
  : std::map<std::string, ConfigSet >()    {}

ConfigsMap::ConfigsMap(const ConfigsMap& other)
  : std::map<std::string,ConfigSet>(other)    {}

ConfigsMap& ConfigsMap::operator=(const ConfigsMap& other){
  std::map<std::string,ConfigSet>::operator=(other);
  return *this;
}

ConfigSet& ConfigsMap::operator[](const std::string& k){
  if( this->find( k ) == this->end() ){
    std::cerr << "Attempting to access a non-existant config set key: " << k << std::endl;
    exit(-1);
  }
  return std::map<std::string,ConfigSet>::operator[](k);
}

std::ostream& operator<<(std::ostream& out, ConfigsMap cm){
  ConfigsMap::iterator it;
  for( it = cm.begin(); it != cm.end(); it++ ){
    out << it->first << " {\n" << it->second <<  "}\n" << std::endl;
  }

  return out;

}

