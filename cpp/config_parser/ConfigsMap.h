#ifndef __CONFIGSMAP_H
#define __CONFIGSMAP_H

#include <map>
#include <string>
#include <iostream>

#include "ConfigSet.h"

class ConfigsMap : public std::map<std::string, ConfigSet > 
{
  public:
    ConfigsMap();
    ConfigsMap(const ConfigsMap& other);

    ConfigsMap& operator=(const ConfigsMap& other);
    ConfigSet& operator[](const std::string& k);

    friend std::ostream& operator<<(std::ostream&, ConfigsMap);
};




#endif
