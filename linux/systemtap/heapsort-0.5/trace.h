// trace.h

#include "config.h"
#ifdef HAVE_SYSTEMTAP
// include the generated probes header and put markers in code
#include "probes.h"
#define TRACE(probe) probe
#else
// Wrap the probe to allow it to be removed when no systemtap available
#define TRACE(probe)
#endif
