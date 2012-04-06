#ifndef __ac_FIRST__home_dgquintas_samples_cpp_aspectc4343__
#define __ac_FIRST__home_dgquintas_samples_cpp_aspectc4343__
#define __ac_FIRST_FILE__home_dgquintas_samples_cpp_aspectc4343_head_h__

#ifndef __ac_h_
#define __ac_h_
namespace AC {
  typedef const char* Type;
  enum JPType { CALL = 0x0004, EXECUTION = 0x0008, CONSTRUCTION = 0x0010, DESTRUCTION = 0x0020 };
  struct Action {
    void **_args; void *_result; void *_target; void *_that; void *_fptr;
    void (*_wrapper)(Action &);
    inline void trigger () { _wrapper (*this); }
  };
  struct AnyResultBuffer {};
  template <typename T> struct ResultBuffer : public AnyResultBuffer {
    char _data[sizeof (T)];
    ~ResultBuffer () { ((T*)_data)->T::~T(); }
    operator T& () const { return *(T*)_data; }
  };
  template <class Aspect, int Index>
  struct CFlow {
    static int &instance () {
      static int counter = 0;
      return counter;
    }
    CFlow () { instance ()++; }
    ~CFlow () { instance ()--; }
    static bool active () { return instance () > 0; }
  };
}
inline void * operator new (unsigned int, AC::AnyResultBuffer *p) { return p; }
inline void operator delete (void *, AC::AnyResultBuffer *) { } // for VC++
#endif // __ac_h_
#endif // __ac_FIRST__home_dgquintas_samples_cpp_aspectc4343__

#line 1 "head.h"

#line 40 "out/head.h"

#ifndef __ac_fwd_Trace__
#define __ac_fwd_Trace__
class Trace;
namespace AC {
  inline void invoke_Trace_Trace_a0_after ();
  inline void invoke_Trace_Trace_a1_around ();
}
#endif

#ifndef __ac_need__home_dgquintas_samples_cpp_aspectc4343_aop_ah__
#define __ac_need__home_dgquintas_samples_cpp_aspectc4343_aop_ah__
#endif

#line 1 "head.h"

#line 57 "out/head.h"
class Trace;

#line 1 "head.h"
class Foo{
#line 62 "out/head.h"
  friend class ::Trace;

#line 1 "head.h"

  public:
    
#line 69 "out/head.h"
public: inline void __exec_old_bar();

#line 3 "head.h"
void bar();
    int lol();
};

#line 77 "out/head.h"

#ifdef __ac_FIRST_FILE__home_dgquintas_samples_cpp_aspectc4343_head_h__
/*** begin of aspect includes ***/
#if !defined(__ac_have__home_dgquintas_samples_cpp_aspectc4343_aop_ah__) && defined(__ac_need__home_dgquintas_samples_cpp_aspectc4343_aop_ah__)
#define __ac_have__home_dgquintas_samples_cpp_aspectc4343_aop_ah__
#include "aop.ah"
#endif
/*** end of aspect includes ***/
#undef __ac_FIRST__home_dgquintas_samples_cpp_aspectc4343__
#undef __ac_FIRST_FILE__home_dgquintas_samples_cpp_aspectc4343_head_h__
#endif // __ac_FIRST_FILE__home_dgquintas_samples_cpp_aspectc4343_head_h__
