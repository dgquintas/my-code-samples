#include <vector>
#include <boost/pool/pool_alloc.hpp>

using namespace std;

void func()
{
  std::vector<int, boost::pool_allocator<int> > v;
//  std::vector<int > v;
  for (int i = 0; i < 10000; ++i)
    v.push_back(13);
} // Exiting the function does NOT free the system memory allocated by the pool allocator
  // You must call
  //  boost::singleton_pool<boost::pool_allocator_tag, sizeof(int)>::release_memory()
  // in order to force that
  //

int main(){
  for(int i=0; i < 10000; i++)
  func();

  return 0;
}
