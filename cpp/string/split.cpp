#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <iostream>

std::vector<std::string> split(const std::string& s)
{
  std::istringstream is(s);
  return std::vector<std::string> (std::istream_iterator<std::string>(is),
      std::istream_iterator<std::string>());
}

int main(){

  std::string str("uno dos tres cuatro");

  std::vector<std::string> v( split(str) );

  for(int i = 0 ; i < v.size(); i++){
    std::cout << v[i] << std::endl;
  }

  return 0;
}
