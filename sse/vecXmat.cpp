#include <iostream>
#include <cstdlib>
#include <xmmintrin.h>
#include <vector>
#include <cassert>


template <typename T, int A >
class MyAlloc {
  public:
    // type definitions
    typedef T        value_type;
    typedef T*       pointer;
    typedef const T* const_pointer;
    typedef T&       reference;
    typedef const T& const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    // rebind allocator to type U
    template <class U>
      struct rebind {
        typedef MyAlloc<U,A> other;
      };

    // return address of values
    pointer address (reference value) const {
      return &value;
    }
    const_pointer address (const_reference value) const {
      return &value;
    }

    /* constructors and destructor
     * - nothing to do because the allocator has no state
     */
    MyAlloc() throw() {
    }
    MyAlloc(const MyAlloc&) throw() {
    }
    template <class U>
      MyAlloc (const MyAlloc<U,A>&) throw() {
      }
    ~MyAlloc() throw() {
    }

    // return maximum number of elements that can be allocated
    size_type max_size () const throw() {
      return std::numeric_limits<std::size_t>::max() / sizeof(T);
    }

    // allocate but don't initialize num elements of type T
    pointer allocate (size_type num, const void* = 0) {
      void* mem;
      //posix_memalign( &mem, A, num * sizeof( value_type ) );
      mem = _mm_malloc(num * sizeof(value_type), A);
      pointer ret = reinterpret_cast< pointer >( mem );
      assert( (((int)ret) % A) == 0 );
      return ret;
    }

    // initialize elements of allocated storage p with value value
    void construct (pointer p, const T& value) {
      // initialize memory with placement new
      new((void*)p)T(value);
    }

    // destroy elements of initialized storage p
    void destroy (pointer p) {
      // destroy objects by calling their destructor
      p->~T();
    }

    // deallocate storage p of deleted elements
    void deallocate (pointer p, size_type num) {
      _mm_free( (void*) p );
    }
};


int main()
{
  //std::vector< float, MyAlloc< float, 16 > > SSEVec1;
  std::vector< float, MyAlloc< float, 16 > > SSEVec1;
  std::vector< float, MyAlloc< float, 16 > > SSEVec2;
  std::vector< float, MyAlloc< float, 16 > > SSEVec3(4);
  

  SSEVec1.push_back( 1.1 );
  SSEVec1.push_back( 2.1 );
  SSEVec1.push_back( 3.1 );
  SSEVec1.push_back( 4.1 );

  SSEVec2.push_back( 1.2 );
  SSEVec2.push_back( 2.2 );
  SSEVec2.push_back( 3.2 );
  SSEVec2.push_back( 4.12);



  const  __m128 a = _mm_load_ps( &(SSEVec1[0]) );
  const  __m128 b = _mm_load_ps( &(SSEVec2[0]) );
  
  std::vector< __m128, MyAlloc< __m128, 16 > > vec128s1;
  std::vector< __m128, MyAlloc< __m128, 16 > > vec128s2;
  std::vector< __m128, MyAlloc< __m128, 16 > > vec128s3;

  vec128s1.reserve(2);
  vec128s2.reserve(2);
  vec128s3.reserve(2);

  vec128s1.push_back(a);
  vec128s1.push_back(b);

  vec128s2.push_back(b);
  vec128s2.push_back(a);

  vec128s3.push_back(_mm_mul_ps( vec128s1[0], vec128s2[0] )); 
  vec128s3.push_back(_mm_mul_ps( vec128s1[1], vec128s2[1] )); 

//  const  __m128 c = _mm_mul_ps( a,b);
  _mm_store_ps( &(SSEVec3[0]),  vec128s3[0]);
 
  for(int i = 0; i < 4 ; i++){
    std::cout << SSEVec1.at(i) << "\t";
  }
  std::cout << std::endl;
  for(int i = 0; i < 4 ; i++){
    std::cout << SSEVec2.at(i) << "\t";
  }
  std::cout << std::endl;
  std::cout << "-----------------------------" << std::endl;
  for(int i = 0; i < 4 ; i++){
    std::cout << SSEVec3.at(i) << "\t";
  }
  std::cout << std::endl;

  return 0;
}
