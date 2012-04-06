#include "C.h"

std::ostream& operator<<(std::ostream& out, const C<int>& c){
  out << c.i;

  return out;
}

