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


template<typename T,int N = 64, int M =32>
class Mivec{
  public:

    Mivec()
      : _lastIndex(0), _lastData(-1)
    { }


    void push_back(T x) {
      if( _lastIndex == 0 ){
        ++_lastData;
        _data[_lastData] = reinterpret_cast<T* const>(_pool::malloc());
        assert( _data[_lastData] != 0 );
      }

      _data[_lastData][_lastIndex] = x;
      if( ++_lastIndex == N){
        _lastIndex=0;
      }
    }
    
    T& get(int i){
      size_t dataIdx = i >> (boost::static_log2< N >::value);
      size_t innerIdx = i & (N-1);
      return _data[dataIdx][innerIdx];
    }
    int size() const{
      if( _lastData < 0 ){
        return 0;
      }
      return ((_lastData-1)*N) + _lastIndex ;
    }

    ~Mivec(){
      for(int i=0; i <= _lastData; ++i){
        _pool::free(_data[i]);
      }
    }

  private:
    T * _data[M];
    int _lastIndex;
    int _lastData;
    typedef boost::singleton_pool<Mivec, N*sizeof(T)> _pool; 

};


int J;
int I;

void withPool()
{

  clock_t t1;
  t1 = clock();
  for(int j=0; j < J; ++j){
    Mivec<int> v;
    for(int i=0; i < I; ++i){
      v.push_back(i);
    }
  }
  std::cout << (clock() - t1) / ((double)CLOCKS_PER_SEC) << std::endl;
}


void withoutPool()
{
  clock_t t1;
  t1 = clock();
  for(int j=0; j < J; ++j){
    std::vector<int> v2(I);
    for(int i=0; i < I; ++i){
      v2.push_back(i);
    }
  }
  std::cout << (clock() - t1) / ((double)CLOCKS_PER_SEC) << std::endl;

}


int main(int argc, char** argv){

  J = atoi(argv[1]);
  I = atoi(argv[2]);

  withPool();
  withoutPool();



  return 0;
}



