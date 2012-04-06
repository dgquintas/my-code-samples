#include <boost/integer/static_log2.hpp>  // for boost::static_log2
#include <iostream>  // for std::cout (std::endl indirectly)
int main()
{
  std::cout << boost::static_log2< 32 >::value << std::endl;
  return 0;
}
