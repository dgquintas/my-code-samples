#include <stdio.h>
#include <tmmintrin.h>
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

__m128i a, b, c;

// _mm_load_pd and _mm_store_pd: The address must be 16-byte aligned


int16_t left[8] __attribute__((aligned(16))) = { 1,2,3,4,5,6,7,8 };
int16_t right[8] __attribute__((aligned(16))) = { 61,51,41,31,21,11,1,9 };
int16_t out[8] __attribute__((aligned(16)));

int main(void){
int i;
int64_t t1,t2;

printf("Usual way...\n");



float classic_sse1;

RDTSC(t1);
classic_sse1 = 0;
classic_sse1 += left[0];
classic_sse1 += left[1];
classic_sse1 += left[2];
classic_sse1 += left[3];
classic_sse1 += left[4];
classic_sse1 += left[5];
classic_sse1 += left[6];
classic_sse1 += left[7];

classic_sse1 += right[0];
classic_sse1 += right[1];
classic_sse1 += right[2];
classic_sse1 += right[3];
classic_sse1 += right[4];
classic_sse1 += right[5];
classic_sse1 += right[6];
classic_sse1 += right[7];

RDTSC(t2);
printf("%lld ciclos classic_sse1\n", t2-t1);
printf("Result CLASSIC SSE1: %.10f\n",classic_sse1);    


a = _mm_load_si128((__m128i const*)left);
b = _mm_load_si128((__m128i const*)right);

RDTSC(t1);
a = _mm_hadd_epi16(a,b);
a = _mm_hadd_epi16(a,a);
a = _mm_hadd_epi16(a,a);
a = _mm_hadd_epi16(a,a);
RDTSC(t2);
printf("%lld ciclos sse3 float\n", t2-t1);

//RDTSC(t1);
//b= _mm_add_ps(b, _mm_movehl_ps(b,b));
//b= _mm_add_ps(b, _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 2, 1, 1)));
//RDTSC(t2);
//printf("%lld ciclos sse\n", t2-t1);

_mm_store_si128((__m128i*)out, a);

printf("Result sse3 float:\n");
printf("%d \n", out[0]);




return 0; 
}
