#include <string>
#include <iostream>

std::string strip(const std::string& str, const std::string SEPSET = " \t"){

  const std::string::size_type first = str.find_first_not_of(SEPSET);
  return ( first==std::string::npos ) ? 
    std::string()  
    :
    str.substr(first, str.find_last_not_of(SEPSET)-first+1);
}


int main(){

  std::string str("  hola hola bla bla       ");

  std::cout << str << "|" << std::endl;

  std::cout << strip(str, "\t ") << "|" << std::endl;
  std::cout << strip(str, "\t") << "|" << std::endl;


  return 0;
}


