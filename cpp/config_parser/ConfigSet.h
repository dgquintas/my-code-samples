#ifndef __CONFIGSET_H
#define __CONFIGSET_H

#include <map>
#include <iostream>

#include "GenericValue.h"

class ConfigSet : public std::map<std::string,GenericValue>
{
  public:
    ConfigSet();
    ConfigSet(const ConfigSet& other);

    ConfigSet& operator=(const ConfigSet& other);
    GenericValue& operator[](const std::string& k);

    friend std::ostream& operator<<(std::ostream&, ConfigSet);

};

#endif
