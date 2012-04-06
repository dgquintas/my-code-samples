
namespace mpplas{
  const int OPT_LEVEL = 3;
  const char* const TARGET_ARCH = "x86";
  const bool DEBUG_ENABLED = true;
  const bool PROFILING_ENABLED = false;
  const bool OPENMP_ENABLED =false;
  const int RELEASE_VERSION = 123;
  const char* const SIMD_KERNEL = "sse2";
};

int main(){
  int x = mpplas::OPT_LEVEL;
  return 0;
  }

