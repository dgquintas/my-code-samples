#include "ConfigParser.h"
#include <cstdio>


ConfigParser::ConfigParser()
  : _configFile(""), _map()
{}

  const std::auto_ptr< ConfigParser > ConfigParser::singletonInstance( new ConfigParser() );

  ConfigParser* ConfigParser::getInstance() {
    return singletonInstance.get();
  }


void ConfigParser::appendPairToSet(const std::string& setKey, 
    const std::string& key, 
    const GenericValue& value) {
  if( _map.find(setKey) != _map.end() ){
    ConfigSet& cs(_map[setKey]);
    if(cs.find(key) != cs.end()){
      cs[key] = value;
    }
    else{
      cs.insert( std::pair<std::string, GenericValue>(key,value));
    }
  }
  else{
    ConfigSet cs;
    cs.insert(std::pair<std::string, GenericValue>(key,value));
    _map.insert(std::pair<std::string, ConfigSet>(setKey,cs));
  }

  return;
}


ConfigsMap ConfigParser::getParsedConfigs(const std::string& configFilename) const{
  extern int yyparse(void);
  extern FILE* yyin;
  extern FILE* yyout;

  yyin = fopen( configFilename.c_str(), "r" );
  if( yyin == NULL){
    std::cerr << "The specified configuration file (" 
      << configFilename 
      << ") cannot be read" << std::endl;
    exit(-1);
  }
  yyout = stdout;

  yyparse();
  fclose( yyin );
  return _map; 
}
