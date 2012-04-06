#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>
//#include "Herramientas.c"



#define SUBK 16


void resetXMM(void)
{
  __asm__ __volatile__ (
      "xorps %%xmm0, %%xmm0 \n\t"
      "xorps %%xmm1, %%xmm1 \n\t"
      "xorps %%xmm2, %%xmm2 \n\t"
      "xorps %%xmm3, %%xmm3 \n\t"
      "xorps %%xmm4, %%xmm4 \n\t"
      "xorps %%xmm5, %%xmm5 \n\t"
      "xorps %%xmm6, %%xmm6 \n\t"
      "xorps %%xmm7, %%xmm7 \n\t"
      :
      :
      );
}

inline void opsL0(float *a, float *b1, float *b2, float *b3, float *b4, float *b5 )  __attribute__((always_inline));
inline void opsL0(float *a, float *b1, float *b2, float *b3, float *b4, float *b5 ) 
{
  /* recibe dos vectores de:
   * a -> (1 x k)
   * b -> (k x 5)
   *
   * deja en los registros xmm[3-7] el resultado 
   * de este producto vector por matriz.
   * es necesario invocar a la función sumaRegsTemp
   * para sacar algo en limpio.
   */
  __asm__ __volatile__ (
 
      /***************************************************************
       ***************************************************************
       ********************* PRIMERA ITERACIÓN ***********************
       ***************************************************************
      ***************************************************************/
      /* precargar desde a */
      "prefetcht0 16%[_a] \n\t"
      /* cargar 4 elementos de a */
      "movaps %[_a], %%xmm0 \n\t"
      /* cargar 4 elementos de b */
      "movaps %[_b1], %%xmm1 \n\t" 
      /* cargar otros 4 elementos de b */
      "movaps %[_b2], %%xmm2 \n\t"   
      /* multiplicación y acumulación 
       * %%xmm1 queda disponible */
      "mulps %%xmm0, %%xmm1 \n\t"
      "addps %%xmm1, %%xmm3 \n\t"
 
      /* carga adelantada de los siguientes
       * 4 elementos de b */
      "movaps %[_b3], %%xmm1 \n\t"
      /* multiplicación y suma por %%xmm2.
       * %%xmm2 queda disponible */
      "mulps %%xmm0, %%xmm2 \n\t"
      "addps %%xmm2, %%xmm4 \n\t"
 
      /* carga adelantada de los siguientes
       * 4 elementos de b */
      "movaps %[_b4], %%xmm2 \n\t" 
      /* multiplicación y suma por %%xmm1.
       * %%xmm1 queda disponible */
      "mulps %%xmm0, %%xmm1 \n\t"
      "addps %%xmm1, %%xmm5 \n\t"

      /* carga adelantada de los siguientes
       * 4 elementos de b */
      "movaps %[_b5], %%xmm1 \n\t"
      /* multiplicación y suma por %%xmm1.
       * %%xmm2 queda disponible */
      "mulps %%xmm0, %%xmm2 \n\t"
      "addps %%xmm2, %%xmm6 \n\t"

      /* multiplicación y suma por %%xmm1.
       * %%xmm1 queda disponible */
      "mulps %%xmm0, %%xmm1 \n\t"
      "addps %%xmm1, %%xmm7 \n\t"

      /* fin del cuerpo básico */
      /***************************************************************
       ***************************************************************
       ********************* SEGUNDA ITERACIÓN ***********************
       ***************************************************************
       ***************************************************************/
      /* precargar desde a */
      "prefetcht0 32%[_a] \n\t"
      /* cargar 4 elementos de a */
      "movaps 16%[_a], %%xmm0 \n\t"
      /* cargar 4 elementos de b */
      "movaps 16%[_b1], %%xmm1 \n\t" 
      /* cargar otros 4 elementos de b */
      "movaps 16%[_b2], %%xmm2 \n\t"   
      /* multiplicación y acumulación 
       * %%xmm1 queda disponible */
      "mulps %%xmm0, %%xmm1 \n\t"
      "addps %%xmm1, %%xmm3 \n\t"

      /* carga adelantada de los siguientes
       * 4 elementos de b */
      "movaps 16%[_b3], %%xmm1 \n\t"
      /* multiplicación y suma por %%xmm2.
       * %%xmm2 queda disponible */
      "mulps %%xmm0, %%xmm2 \n\t"
      "addps %%xmm2, %%xmm4 \n\t"

      /* carga adelantada de los siguientes
       * 4 elementos de b */
      "movaps 16%[_b4], %%xmm2 \n\t"
      /* multiplicación y suma por %%xmm1.
       * %%xmm1 queda disponible */
      "mulps %%xmm0, %%xmm1 \n\t"
      "addps %%xmm1, %%xmm5 \n\t"

      /* carga adelantada de los siguientes
       * 4 elementos de b */
      "movaps 16%[_b5], %%xmm1 \n\t"
      /* multiplicación y suma por %%xmm1.
       * %%xmm2 queda disponible */
      "mulps %%xmm0, %%xmm2 \n\t"
      "addps %%xmm2, %%xmm6 \n\t"

      /* multiplicación y suma por %%xmm1.
       * %%xmm1 queda disponible */
      "mulps %%xmm0, %%xmm1 \n\t"
      "addps %%xmm1, %%xmm7 \n\t"

      /* fin del cuerpo básico */     
      /***************************************************************
       ***************************************************************
       ********************* TERCERA ITERACIÓN ***********************
       ***************************************************************
       ***************************************************************/ 
     /* precargar desde a */
      "prefetcht0 48%[_a] \n\t"
      /* cargar 4 elementos de a */
      "movaps 32%[_a], %%xmm0 \n\t"
      /* cargar 4 elementos de b */
      "movaps 32%[_b1], %%xmm1 \n\t" 
      /* cargar otros 4 elementos de b */
      "movaps 32%[_b2], %%xmm2 \n\t"   
      /* multiplicación y acumulación 
       * %%xmm1 queda disponible */
      "mulps %%xmm0, %%xmm1 \n\t"
      "addps %%xmm1, %%xmm3 \n\t"

      /* carga adelantada de los siguientes
       * 4 elementos de b */
      "movaps 32%[_b3], %%xmm1 \n\t"
      /* multiplicación y suma por %%xmm2.
       * %%xmm2 queda disponible */
      "mulps %%xmm0, %%xmm2 \n\t"
      "addps %%xmm2, %%xmm4 \n\t"

      /* carga adelantada de los siguientes
       * 4 elementos de b */
      "movaps 32%[_b4], %%xmm2 \n\t"
      /* multiplicación y suma por %%xmm1.
       * %%xmm1 queda disponible */
      "mulps %%xmm0, %%xmm1 \n\t"
      "addps %%xmm1, %%xmm5 \n\t"

      /* carga adelantada de los siguientes
       * 4 elementos de b */
      "movaps 32%[_b5], %%xmm1 \n\t"
      /* multiplicación y suma por %%xmm1.
       * %%xmm2 queda disponible */
      "mulps %%xmm0, %%xmm2 \n\t"
      "addps %%xmm2, %%xmm6 \n\t"

      /* multiplicación y suma por %%xmm1.
       * %%xmm1 queda disponible */
      "mulps %%xmm0, %%xmm1 \n\t"
      "addps %%xmm1, %%xmm7 \n\t"

      /* fin del cuerpo básico */
      /***************************************************************
       ***************************************************************
       ********************* CUARTA  ITERACIÓN ***********************
       ***************************************************************
       ***************************************************************/
     /* precargar desde a */
      "prefetcht0 64%[_a] \n\t"
      /* cargar 4 elementos de a */
      "movaps 48%[_a], %%xmm0 \n\t"
      /* cargar 4 elementos de b */
      "movaps 48%[_b1], %%xmm1 \n\t" 
      /* cargar otros 4 elementos de b */
      "movaps 48%[_b2], %%xmm2 \n\t"   
      /* multiplicación y acumulación 
       * %%xmm1 queda disponible */
      "mulps %%xmm0, %%xmm1 \n\t"
      "addps %%xmm1, %%xmm3 \n\t"

      /* carga adelantada de los siguientes
       * 4 elementos de b */
      "movaps 48%[_b3], %%xmm1 \n\t"
      /* multiplicación y suma por %%xmm2.
       * %%xmm2 queda disponible */
      "mulps %%xmm0, %%xmm2 \n\t"
      "addps %%xmm2, %%xmm4 \n\t"

      /* carga adelantada de los siguientes
       * 4 elementos de b */
      "movaps 48%[_b4], %%xmm2 \n\t"
      /* multiplicación y suma por %%xmm1.
       * %%xmm1 queda disponible */
      "mulps %%xmm0, %%xmm1 \n\t"
      "addps %%xmm1, %%xmm5 \n\t"

      /* carga adelantada de los siguientes
       * 4 elementos de b */
      "movaps 48%[_b5], %%xmm1 \n\t"
      /* multiplicación y suma por %%xmm1.
       * %%xmm2 queda disponible */
      "mulps %%xmm0, %%xmm2 \n\t"
      "addps %%xmm2, %%xmm6 \n\t"

      /* multiplicación y suma por %%xmm1.
       * %%xmm1 queda disponible */
      "mulps %%xmm0, %%xmm1 \n\t"
      "addps %%xmm1, %%xmm7 \n\t"

      /* fin del cuerpo básico */

      : 
      : [_a] "m" (*a), [_b1] "m" (*b1), [_b2] "m" (*b2),[_b3] "m" (*b3),[_b4] "m" (*b4),[_b5] "m" (*b5)
      );
}

void sumaRegsTemp(float *c)
{
  __asm__ __volatile__ (
      /* "arrejuntar" el resultado 
       * Disponibles %%xmm1 y %%xmm2 
       * Ha de aplicarse la reorganización
       * a %%xmm[3-7]
       *
       * Es claro que "c" habrá de tener reservado espacio para
       * una matrix de dims. 1x5.
       * Vease func. opsL0(a,b)
       * */
      "prefetcht0 %[_c] \n\t"
      /********************/
      /******* xmm3 *******/
      /********************/
      "movaps %%xmm3, %%xmm1 \n\t"
      "shufps $238, %%xmm3, %%xmm1 \n\t"
      
      "addps %%xmm1, %%xmm3 \n\t"
      /* xmm1 dispnonible */
  
      "movaps %%xmm3, %%xmm1 \n\t"
      "shufps $224, %%xmm3, %%xmm1 \n\t"
      
      "addps %%xmm1, %%xmm3 \n\t"
      /* xmm1 dispnonible */

      "shufps $229, %%xmm3, %%xmm3 \n\t"
      "addss %[_c], %%xmm3 \n\t"
      "movss %%xmm3, %[_c] \n\t"
 
      /********************/
      /******* xmm4 *******/
      /********************/
      "movaps %%xmm4, %%xmm1 \n\t"
      "shufps $238, %%xmm4, %%xmm1 \n\t"
      
      "addps %%xmm1, %%xmm4 \n\t"
      /* xmm1 dispnonible */
  
      "movaps %%xmm4, %%xmm1 \n\t"
      "shufps $224, %%xmm4, %%xmm1 \n\t"
      
      "addps %%xmm1, %%xmm4 \n\t"
      /* xmm1 dispnonible */

      "shufps $229, %%xmm4, %%xmm4 \n\t"
      "addss 4%[_c], %%xmm4 \n\t"
      "movss %%xmm4, 4%[_c] \n\t"

      /********************/
      /******* xmm5 *******/
      /********************/
      "movaps %%xmm5, %%xmm1 \n\t"
      "shufps $238, %%xmm5, %%xmm1 \n\t"
      
      "addps %%xmm1, %%xmm5 \n\t"
      /* xmm1 dispnonible */
  
      "movaps %%xmm5, %%xmm1 \n\t"
      "shufps $224, %%xmm5, %%xmm1 \n\t"
      
      "addps %%xmm1, %%xmm5 \n\t"
      /* xmm1 dispnonible */

      "shufps $229, %%xmm5, %%xmm5 \n\t"
      "addss 8%[_c], %%xmm5 \n\t"
      "movss %%xmm5, 8%[_c] \n\t"
  

      /********************/
      /******* xmm6 *******/
      /********************/
      "movaps %%xmm6, %%xmm1 \n\t"
      "shufps $238, %%xmm6, %%xmm1 \n\t"
      
      "addps %%xmm1, %%xmm6 \n\t"
      /* xmm1 dispnonible */
  
      "movaps %%xmm6, %%xmm1 \n\t"
      "shufps $224, %%xmm6, %%xmm1 \n\t"
      
      "addps %%xmm1, %%xmm6 \n\t"
      /* xmm1 dispnonible */

      "shufps $229, %%xmm6, %%xmm6 \n\t"
      "addss 12%[_c], %%xmm6 \n\t"
      "movss %%xmm6, 12%[_c] \n\t"


      /********************/
      /******* xmm7 *******/
      /********************/
      "movaps %%xmm7, %%xmm1 \n\t"
      "shufps $238, %%xmm7, %%xmm1 \n\t"
      
      "addps %%xmm1, %%xmm7 \n\t"
      /* xmm1 dispnonible */
  
      "movaps %%xmm7, %%xmm1 \n\t"
      "shufps $224, %%xmm7, %%xmm1 \n\t"
      
      "addps %%xmm1, %%xmm7 \n\t"
      /* xmm1 dispnonible */

      "shufps $229, %%xmm7, %%xmm7 \n\t"
      "addss 16%[_c], %%xmm7 \n\t"
      "movss %%xmm7, 16%[_c] \n\t"

      
      : [_c] "=m" (*c)
      : "m" (*c)
      : "memory"
      );
}



void opsL1(float *c,float *a, float *b, float* bL1, size_t k, size_t m, 
           size_t K, size_t M, size_t N)
{
  /* función encargada de montar las cosas para dar a opsL0 lo que
   * necesita. 
   * - opsL1 te dará lo que necesitas... 
   * - sí por favor, en forma de (1 x k) y (k x 5)
   *
   *   Trabaja (ie, espera de L2) con matrices:
   *   a -> m x k 
   *   b -> k x n ( m = n)
   *   c -> m x n ( m = n)
   *
   *   Dado que estas dimensiones se ha cuidado que sean multiplos de
   *   las esperadas por opsL0, no habra condiciones de frontera.
   *   Ahora bien, puede que la matriz más general no sea multiplo de
   *   las dimensiones anteriormente citadas. Esto *NO* importa a ojos
   *   de opsL1, que siempre recibira, como se ha dicho, esas
   *   dimensiones. Esto es asi ya que se rellenará con ceros en opsL2
   *   de ser necesario.
   *   */

  size_t i,j,p,l;
  register size_t kDieciseisavos = k >> 4;
  register size_t mQuintos = m / 5;
  float *aInicial = a;
  float *cInicial = c;
  resetXMM(); /* por si acaso */

  /* magic numbers 
   * El cinco viene de las dims. para b requeridas por opsL0.
   */
  for(l=0; l < mQuintos; l++){
    register size_t posbL1 = 0;
    for(j=0; j < 5; j++){
      /* recordar que "b" es solo un puntero al inicio del 
       * bloque. Se requiere la copia a un bloque "absoluto" 
       * para opsL0 */
      memcpy(&bL1[posbL1], b, k*sizeof(float));
      posbL1 += k;
      b += K;
    }
      

    posbL1 = 0;
    for(p=0; p < m; p++){
      for(i=0; i < kDieciseisavos; i++){
        opsL0(&a[posbL1],
            &bL1[posbL1],
            &bL1[posbL1]+(k),
            &bL1[posbL1]+(k*2),
            &bL1[posbL1]+(k*3),
            &bL1[posbL1]+(k*4)
            );
        posbL1 += 16;
      }
      sumaRegsTemp(c);
#ifdef DEBUG
      //printf("%f, %f, %f, %f, %f\n", c[0], c[1], c[2], c[3], c[4]);
#endif

      c += N;
      a += K; /* cambio de fila */
      posbL1 = 0;
      resetXMM();
    }
    a = aInicial;
    c = cInicial + (5*(l+1)); 
    /* este 5 sale de que n' (num. de cols. de b' que se cogen en el buffer) es 5 */
  }


  return;
}

void opsL2(float *c, float *a, float *b, const size_t K, const size_t M, const size_t N, const size_t k, const size_t mn)
{ 
  /* partir las matrices mas generales en bloques de:
   *  para A : m x k
   *  para B : k x m
   */
  
  /* la mat. A no es necesario copiarla, ya que sus valores ya son
   * contiguos si se pasa "fila a fila" */

  /* la B en ppio. tampoco por lo mismo. 
   *
   * Ahora bien, para que esto se sostenga, A debe de estar
   * inicialmente por filas (o bien por columnas y luego transpuesta)
   * y B por columnas */

  /* las dimensiones de las matrices mas generales son:
   * C: (M x N)
   * A: (M x K)
   * B: (K x N)
   */
  
  /* teoria del cálculo del tamaño optimo de bloques
   *
   * Se ha de conseguir el mayor k <= kMax que cumpla las siguientes
   * condiciones:
   * 1) Que sea múltiplo  del producto del tamaño del pipeline de las
   * SIMD utilizadas y el número de iteraciones desenrolladas "a mano"
   * en opsL0.  En el caso 3dnow -> 8   (2*4)
   * En el caso SSE   -> 16  (4*4)
   *
   */ 

  float *bL1 = memalign(128,5*4*k);
  register size_t i,j,p;
  const size_t topeK = K-(K%k);
  float *bloqueB;

  for(j=0; j < N; j+=mn){
    for(p=0; p < topeK; p+=k){
      bloqueB = &b[j*K + p];
      for(i=0; i < M; i+=mn)
        opsL1(&c[i*N + j],&a[i*K + p],bloqueB, bL1, k, mn, K, M,N);
    }
    for(; p < K; p+=SUBK){
      bloqueB = &b[j*K + p];
      for(i=0; i < M; i+=mn)
        opsL1(&c[i*N + j],&a[i*K + p],bloqueB, bL1, SUBK, mn, K, M,N);
    }
  }
  


  free(bL1);
  return;
}

void naive(float *c, float *a, float *b, const size_t K, const size_t M, const size_t N)
{
  register int j,p,i;
  for(j=0; j < N; j++)
    for(p=0; p < K; p++)
      for(i=0; i < M; i++)
        c[i*N + j] += a[i*K + p] * b[j*K + p];

}

int main(int argc, char** argv)
{
  float *a, *b, *c;
  int i,j;
  size_t M,N,K, rep;
  
   size_t k;  /* k <= (L1/2)/(6*sizeof(float)) **/ 
                    /* HA DE SER MULTIPLO DE 16 (SSE) */
   size_t mn;  /* mn <= (L2/2)/(2*k*sizeof(float)) */
                    /* HA DE SER MULTIPLO DE 5 */

  if( argc == 7 ){
    M = atoi(argv[1]);
    N = atoi(argv[2]);
    K = atoi(argv[3]);
    k = atoi(argv[4]);
    mn = atoi(argv[5]);
    rep = atoi(argv[6]);
  }
  else{
    fprintf(stderr, "USO: %s M N K tam_bloque_k tam_bloque_mn repeticiones\n", argv[0]);
    return -1;
  }
 
  double flops=2.0*M*N*K;
  size_t paddingK, paddingM, paddingN;
  if( K % SUBK )
  paddingK = SUBK - (K % SUBK); 
  else 
    paddingK = 0;
K += paddingK;

  if( N % mn )
  paddingN = mn - (N % mn); 
  else 
    paddingN = 0;
N += paddingN;

  if( M % mn )
  paddingM = mn - (M % mn); 
  else 
    paddingM = 0;
  M += paddingM;
  
  a = memalign(128,M*K*sizeof(float));
  b = memalign(128,K*N*sizeof(float));
  c = memalign(128,M*N*sizeof(float));


  memset(a,0,M*K*sizeof(float));
  memset(b,0,K*N*sizeof(float));
  
  for(i=0; i<M-paddingM; i++){
    for(j=0; j < K-paddingK; j++){
      a[i*K + j] = (rand() % 100);
    }
  }
  for(i=0; i<N-paddingN; i++){
    for(j=0; j < K-paddingK; j++){
      b[i*K + j] = (rand() % 100);
    }
  }


#ifdef DEBUG 
  for(i=0; i<M; i++){
    for(j=0; j < K; j++){
      printf("%.2f ", a[i*K +j]);
    }
    printf("\n");
  }
  printf("\n");
 
  for(i=0; i<N; i++){
    for(j=0; j < K; j++){
      printf("%.2f ", b[i*K +j]);
    }
    printf("\n");
  }
  printf("\n");
#endif
  
  memset(c,0,M*N*sizeof(float));

  double tiempo=0;
  double tiempoFinal = DBL_MAX;
 
  double flopsMio, flopsAtlas, flopsNaive;
  
  for(i=0; i < rep; i++){
    memset(c,0,M*N*sizeof(float));
//    tiempo = Tiempo();

    opsL2(c,a,b,K,M,N,k,mn); /* ... K,M,N */

//    tiempo = Tiempo() - tiempo;
//    if( tiempo < tiempoFinal ) 
//      tiempoFinal = tiempo;
  }
  //Dump_Ascii_Float("SSE_Matriz_C.txt", M, N, POR_FILAS, c);
//  Dump_Bin_Float("SSE_Matriz_C.dat", M, N, POR_FILAS, c);
  flopsMio = flops   / tiempoFinal / 1.0e6;
  //printf("%f\n", flopsMio);
#ifdef DEBUG
  for(i=0; i < M; i++){
    for(j=0; j < N; j++)
      printf("%.2f ", c[i*N +j]);
    printf("\n");
  }
#endif

  float d_one = 1.0;
 
  tiempo=0;
  tiempoFinal = DBL_MAX;
 
//  for(i=0; i < rep; i++){
//    memset(c,0,M*N*sizeof(float));
//    tiempo = Tiempo();
//    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, M,N,K, d_one,
//        a, K, b, K, d_one, c, N);
//    tiempo = Tiempo() - tiempo;
//
//
//    if( tiempo < tiempoFinal ) 
//      tiempoFinal = tiempo;
//  }
//  flopsAtlas = flops   / tiempoFinal / 1.0e6;
//  //printf("%f\n", flopsAtlas);
//  //Dump_Ascii_Float("ATLAS_Matriz_C.txt", M, N, POR_FILAS, c);
////  Dump_Bin_Float("ATLAS_Matriz_C.dat", M, N, POR_FILAS, c);
//
//  printf("%f\n", flopsMio/flopsAtlas);
  
#ifdef DEBUG
  for(i=0; i < M; i++){
    for(j=0; j < N; j++)
      printf("%.2f ", c[i*N +j]);
    printf("\n");
  }
#endif

  tiempo=0;
  tiempoFinal = DBL_MAX;

  
//  for(i=0; i < rep; i++){
//    memset(c,0,M*N*sizeof(float));
//    tiempo = Tiempo();
//
//    naive(c,a,b,K,M,N); /* ... K,M,N */
//    tiempo = Tiempo() - tiempo;
//    if( tiempo < tiempoFinal ) 
//      tiempoFinal = tiempo;
//  }
////  Dump_Ascii_Float("SSE_Matriz_C.txt", M, N, POR_FILAS, c);
////  Dump_Bin_Float("Naive_Matriz_C.dat", M, N, POR_FILAS, c);
//  flopsNaive = flops   / tiempoFinal / 1.0e6;
//  printf("%f\n", flopsNaive);

  
  free(a);
  free(b);
  free(c);
  return 0;
}

