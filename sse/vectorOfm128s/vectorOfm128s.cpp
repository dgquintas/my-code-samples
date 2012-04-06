#include <vector>
#include <iostream>
#include <emmintrin.h>
#include <cassert>

template <typename T, int A >
class SSEAlloc {
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
        typedef SSEAlloc<U,A> other;
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
    SSEAlloc() throw() {
    }
    SSEAlloc(const SSEAlloc&) throw() {
    }
    template <class U>
      SSEAlloc (const SSEAlloc<U,A>&) throw() {
      }
    ~SSEAlloc() throw() {
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
 
struct Wrapper{

  Wrapper() {};
  Wrapper(__m128 x) 
    : data(x)
  {};

  inline void foo(){ 
    int a;
    float b;
    b +=a;

    return;
  }
  __m128 data;
};

int main(){


  std::vector<Wrapper, SSEAlloc< Wrapper, 16 > > vec;

  Wrapper af,bf;

  std::cout << sizeof(__m128) << std::endl;
  std::cout << sizeof(Wrapper) << std::endl;


  float inp_sse1[4] __attribute__((aligned(16))) = { 2.2, 3.3, 1.1, -2.2 };
  float inp_sse2[4] __attribute__((aligned(16))) = { 5.2, 6.3, 7.1, -8.2 };

  af.data = _mm_load_ps(inp_sse1);
  bf.data = _mm_load_ps(inp_sse2);

  vec.push_back(af);
  vec.push_back(bf);

  float* ptr = (float*)&(vec[0]);
//  float* ptr = (float*)(&af);

  for(int i=0; i < vec.size()*4; i++){
    std::cout << ptr[i] << " ";
  }


  for(int i=0; i < vec.size()*4; i++){
    ptr[i] = i*2.2;
  }
  std::cout << std::endl << std::endl;

  float* const base = (float*)(&vec[0]);

  
  for(int i=0; i < 4; i++){
    std::cout << base[i] << std::endl;
  }



  std::cout << std::endl;


  return 0;
}
