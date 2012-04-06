#include <boost/any.hpp>
#include <iostream>
#include <string>


using boost::any_cast;

int main(){

  boost::any bla = 1;
  boost::any ble = 1.1;
  boost::any bli = std::string("lol");

  std::cout << any_cast(bla) << std::endl;

  return 0;
}
