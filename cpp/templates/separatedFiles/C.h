#include <iostream>
template<typename T>
class C{
  public:
    C(T x) : i(x) {}
    T i;
};

std::ostream& operator<<(std::ostream& out, const C<int>& c);

