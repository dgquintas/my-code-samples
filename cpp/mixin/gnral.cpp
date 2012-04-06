#include "gnral.h"

template<> const std::auto_ptr<Gnral> Mixin<Gnral>::instance( new Gnral() );
