
/** based on C++ Templates by David Vandevoorde and Nicolai M. Josuttis.
 * page 302 
 * http://www.josuttis.com/tmplbook/meta/pow3.hpp.html
 */
template<int B, int N>
class Pow {
  public:
    enum { result = B * Pow<B,N-1>::result };
};

template<int B>
class Pow<B,1>{
  public:
    enum { result = B } ;
};



