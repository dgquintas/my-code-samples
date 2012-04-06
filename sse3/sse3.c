#include <stdio.h>
#include <pmmintrin.h>
#include <inttypes.h>

#define RDTSC(x) asm( "rdtsc;" : "=A"(x)  );


/*
* 
* Compiling:
* 
* gcc -march=pentium4 -msse3 -o gcc_sse3  gcc_sse3.c
*
*   with latest gcc you can use also -march=prescott switch
*
*/

// __m128d : these 128 bits can contain two double precision floating point numbers

__m128 a, b, c;
__m128d a2, b2, c2;

// _mm_load_pd and _mm_store_pd: The address must be 16-byte aligned


float inp_sse1[4] __attribute__((aligned(16))) = { 3560000,7100959, 3440000,2070001 };
double inp_sse2[2] __attribute__((aligned(16))) = { 42.23521353,50.25000005};

int main(void){
int i;
int64_t t1,t2;

printf("Usual way...\n");



float classic_sse1;
double classic_sse2;

RDTSC(t1);
classic_sse1 = inp_sse1[0] + inp_sse1[1] + inp_sse1[2] + inp_sse1[3];
RDTSC(t2);
printf("%lld ciclos classic_sse1\n", t2-t1);
printf("Result CLASSIC SSE1: %.10f\n",classic_sse1);    

RDTSC(t1);
classic_sse2 = inp_sse2[0] + inp_sse2[1];
RDTSC(t2);
printf("%lld ciclos classic_sse2\n", t2-t1);
printf("Result CLASSIC SSE2: %.10f\n",classic_sse2);    

a = _mm_load_ps(inp_sse1);
b = a;

RDTSC(t1);
a = _mm_hadd_ps(a, a);
a = _mm_hadd_ps(a, a);
RDTSC(t2);
printf("%lld ciclos sse3 float\n", t2-t1);


RDTSC(t1);
b= _mm_add_ps(b, _mm_movehl_ps(b,b));
b= _mm_add_ps(b, _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 2, 1, 1)));
RDTSC(t2);
printf("%lld ciclos sse\n", t2-t1);


float res,res2;
_mm_store_ss(&res, a);
_mm_store_ss(&res2, b);

printf("Result sse3 float: %.10f\n",res);
printf("Result sse: %.10f\n",res2);


a2 = _mm_load_pd(inp_sse2);
b2 = a2;

RDTSC(t1);
a2 = _mm_hadd_pd(a2, a2);
RDTSC(t2);
printf("%lld ciclos sse3 double\n", t2-t1);


RDTSC(t1);
b2= _mm_add_pd(b2, _mm_shuffle_pd(b2, b2, _MM_SHUFFLE2(0, 1)));
RDTSC(t2);
printf("%lld ciclos sse2\n", t2-t1);


double res21,res22;
_mm_store_sd(&res21, a2);
_mm_store_sd(&res22, b2);

printf("Result sse3 double: %.10f\n",res21);
printf("Result sse2: %.10f\n",res22);



return 0; 
}
