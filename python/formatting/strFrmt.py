txt = """
namespace mpplas{
  const int OPT_LEVEL = %d;
  const char* const TARGET_ARCH = "%s";
  const bool DEBUG_ENABLED = %s;
  const bool PROFILING_ENABLED = %s;
  const bool OPENMP_ENABLED =%s;
  const int RELEASE_VERSION = %d;
  const char* const SIMD_KERNEL = "%s";
};

int main(){
  return 0;
  }
"""

res = txt % \
        (3, 
        "x86", 
        str(True).lower(), 
        str(False).lower(), 
        str(False).lower(),
        123,
        "sse2")
print res

