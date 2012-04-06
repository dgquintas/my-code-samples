#define POR_COLUMNAS 0
#define POR_FILAS    1

#define dabs(x)   ((x)<0   ? -(x):(x))
#define max(x, y) ((x)>(y) ?  (x):(y))
#define min(x, y) ((x)<(y) ?  (x):(y))

#define L1_SIZE_LARGE_dirty_cache 32
#define L2_SIZE_LARGE_dirty_cache 1024

#ifdef __ia64__
static __inline unsigned long rdtsc(void) {
  unsigned long clocks;
  __asm__ __volatile__ ("mov %0=ar.itc" : "=r"(clocks));
  return clocks;
}
#else
static inline void rdtsc(unsigned int *high, unsigned int *low){
  asm("rdtsc" : "=a" (*low), "=d"(*high): : "cc");
}
#endif

#ifndef __ia64__
static unsigned int  initialclockoffset;
#endif

static double clocks = 0.;
static int    Primera_Vez_Alea   = 1;

extern void dlarnv_(int *, int *, int *, double *);
