#include <boost/pool/pool_alloc.hpp>
#include <boost/integer/static_log2.hpp>
#include <iostream>
#include <ctime>
#include <cassert>
#include <vector>
#include <deque>
#include <functional>
#include <algorithm>
#include <iterator>

using std::vector;


void withPool()
{

  clock_t t1;
  t1 = clock();
  for(int j=0; j < 200000; ++j){
    std::deque<int, boost::fast_pool_allocator<int> > v;
    for(int i=0; i < 100; ++i){
      v.push_back(i);
    }
  }
  std::cout << (clock() - t1) / ((double)CLOCKS_PER_SEC) << std::endl;
}

void withoutPool()
{
  clock_t t1;
  t1 = clock();
  for(int j=0; j < 200000; ++j){
    std::vector<int> v2;
    for(int i=0; i < 100; ++i){
      v2.push_back(i);
    }
  }
  std::cout << (clock() - t1) / ((double)CLOCKS_PER_SEC) << std::endl;

}

int main(){

  withPool();
  withoutPool();



  return 0;
}



