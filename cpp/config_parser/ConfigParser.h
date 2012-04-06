#ifndef __CONFIGPARSER_H
#define __CONFIGPARSER_H

#include <map>
#include <string>
#include <memory>
#include <utility>

#include "GenericValue.h"
#include "ConfigSet.h"
#include "ConfigsMap.h"
class ConfigParser{
  public:
    static ConfigParser* getInstance() ;

    ConfigsMap getParsedConfigs(const std::string& configFilename) const ;

    void appendPairToSet(const std::string& setKey, 
        const std::string& key, 
        const GenericValue& value);


  private:
    static const std::auto_ptr< ConfigParser > singletonInstance;
    ConfigParser();

    std::string _configFile;
    ConfigsMap _map;


};

#endif
