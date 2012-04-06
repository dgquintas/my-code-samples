#include "Definiciones.h"
#include <cblas.h>

void Valor_Clock(void) {
  FILE *infile;
  char
    buffer[256], *p;
  unsigned int
    high, low;

  if (clocks == 0.) {
    p = (char *)NULL;
    infile = fopen("/proc/cpuinfo", "r");
    while (fgets(buffer, sizeof(buffer), infile)){
      if (!strncmp("cpu MHz", buffer, 6)){
	p = strchr(buffer, ':') + 1;
	break;
      }
    }
    clocks = 1.e6 * atof(p);
    fclose(infile);
#ifndef __ia64__
    rdtsc(&high, &low);
    initialclockoffset = high;
#endif
  }
}

double Tiempo(void){
#ifndef __ia64__
  unsigned int high, low;
  unsigned long long totalclocks;
#else
  unsigned long totalclocks;
#endif
  if (!clocks) Valor_Clock();
#ifndef __ia64__
  rdtsc(&high, &low);
  high -= initialclockoffset;
  totalclocks = (((unsigned long long)high) << 32) | (unsigned long long)low;
#else
  totalclocks = rdtsc();
#endif
  return (double)totalclocks / clocks;
}
void Dump_Ascii_Float(char *nombre_fichero, const int filas, const int columnas, const int tipo, const float *a) {
  /* Vuelca a un fichero texto una matriz/vector */
  /* Formato del fichero:                        */
  /*      filas  columnas TIPO                   */
  /*      dato_1 dato_2 ... dato_filas*columnas  */
  /* Significado de TIPO:                        */
  /*      0: almacenamiento por columnas         */
  /*      1: almacenamiento por filas            */
  FILE *fp;
  int i=0;

  if ((tipo == POR_COLUMNAS) || (tipo == POR_FILAS)) {
    fp=fopen(nombre_fichero, "w");

    /* Escribe cabecera */
    fprintf(fp, "%d  %d  %d\n", filas, columnas, tipo);

    /* Escribe datos (matriz) */
    for (i=0; i<(filas*columnas-1); i++)
      fprintf(fp, "%f  ", a[i]);
    fprintf(fp, "%f\n", a[filas*columnas-1]);
    
    /* cerrar y fin */
    fclose(fp);
  }
  else
    printf("Inconsistencia en argumento 4 en llamada a Dump_Ascii. No se crea el fichero\n");
}

void Dump_Ascii(char *nombre_fichero, const int filas, const int columnas, const int tipo, const double *a) {
  /* Vuelca a un fichero texto una matriz/vector */
  /* Formato del fichero:                        */
  /*      filas  columnas TIPO                   */
  /*      dato_1 dato_2 ... dato_filas*columnas  */
  /* Significado de TIPO:                        */
  /*      0: almacenamiento por columnas         */
  /*      1: almacenamiento por filas            */
  FILE *fp;
  int i=0;

  if ((tipo == POR_COLUMNAS) || (tipo == POR_FILAS)) {
    fp=fopen(nombre_fichero, "w");

    /* Escribe cabecera */
    fprintf(fp, "%d  %d  %d\n", filas, columnas, tipo);

    /* Escribe datos (matriz) */
    for (i=0; i<(filas*columnas-1); i++)
      fprintf(fp, "%f  ", a[i]);
    fprintf(fp, "%f\n", a[filas*columnas-1]);
    
    /* cerrar y fin */
    fclose(fp);
  }
  else
    printf("Inconsistencia en argumento 4 en llamada a Dump_Ascii. No se crea el fichero\n");
}

void Dump_Bin_Float(char *nombre_fichero, const int filas, const int columnas, const int tipo, const float *a) {
  /* Vuelca a un fichero binario una matriz/vector */
  /*      filas  columnas TIPO                     */
  /*      dato_1 dato_2 ... dato_filas*columnas    */
  /* Significado de TIPO:                          */
  /*      0: almacenamiento por columnas           */
  /*      1: almacenamiento por filas              */
  FILE *fp;

  if ((tipo == POR_COLUMNAS) || (tipo == POR_FILAS)) {
    int tmp_filas=filas, tmp_columnas=columnas, tmp_tipo=tipo;
    fp=fopen(nombre_fichero, "w");

    /* Escribe cabecera */
    fwrite(&tmp_filas,    sizeof(int), 1, fp);
    fwrite(&tmp_columnas, sizeof(int), 1, fp);
    fwrite(&tmp_tipo,     sizeof(int), 1, fp);
    
    /* Escribe datos (matriz) */
    fwrite(a, filas*columnas*sizeof(float), 1, fp);
    
    /* cerrar y fin */
    fclose(fp);
  }
  else
    printf("Inconsistencia en argumento 4 en llamada a Dump_Bin. No se crea el fichero\n");
}

void Dump_Bin(char *nombre_fichero, const int filas, const int columnas, const int tipo, const double *a) {
  /* Vuelca a un fichero binario una matriz/vector */
  /*      filas  columnas TIPO                     */
  /*      dato_1 dato_2 ... dato_filas*columnas    */
  /* Significado de TIPO:                          */
  /*      0: almacenamiento por columnas           */
  /*      1: almacenamiento por filas              */
  FILE *fp;

  if ((tipo == POR_COLUMNAS) || (tipo == POR_FILAS)) {
    int tmp_filas=filas, tmp_columnas=columnas, tmp_tipo=tipo;
    fp=fopen(nombre_fichero, "w");

    /* Escribe cabecera */
    fwrite(&tmp_filas,    sizeof(int), 1, fp);
    fwrite(&tmp_columnas, sizeof(int), 1, fp);
    fwrite(&tmp_tipo,     sizeof(int), 1, fp);
    
    /* Escribe datos (matriz) */
    fwrite(a, filas*columnas*sizeof(double), 1, fp);
    
    /* cerrar y fin */
    fclose(fp);
  }
  else
    printf("Inconsistencia en argumento 4 en llamada a Dump_Bin. No se crea el fichero\n");
}

void Load_Ascii(char *nombre_fichero, int filas, int columnas, int tipo, double *a) {
  /* Lee de un fichero ascii una matriz/vector  */
  /* Formato del fichero:                       */
  /*      filas  columnas TIPO                  */
  /*      dato_1 dato_2 ... dato_filas*columnas */
  /* Significado de TIPO:                       */
  /*      0: almacenamiento por columnas        */
  /*      1: almacenamiento por filas           */
  /* OJO: No comprueba errores de EOF()         */
  FILE *fp;
  int i=0, tmp_filas=0, tmp_columnas=0, tmp_tipo=0;
  fp=fopen(nombre_fichero, "r");

  /* Lee cabecera */
  fscanf(fp, "%d%d%d", &tmp_filas, &tmp_columnas, &tmp_tipo);

  if ((tmp_filas==filas) && (tmp_columnas==columnas) && (tmp_tipo==tipo)) 
    /* Lee datos (matriz) */
    for (i=0; i<filas*columnas; i++)
      fscanf(fp, "%lf", &a[i]);
  else
    printf("Inconsistencia entre argumentos 1 al 3 y cabecera del fichero en llamada a Load_Ascii\n");

  /* cerrar y fin */
  fclose(fp);
}

void Load_Cabecera_Ascii(char *nombre_fichero, int *filas, int *columnas, int *tipo) {
  /* Lee la cabecera de un fichero ascii que contiene una matriz/vector  */
  /* Formato del fichero:                                                */
  /*      filas  columnas TIPO                                           */
  /* Significado de TIPO:                                                */
  /*      0: almacenamiento por columnas                                 */
  /*      1: almacenamiento por filas                                    */
  /* OJO: No comprueba errores de EOF()                                  */
  FILE *fp;
  fp=fopen(nombre_fichero, "r");

  /* Lee cabecera */
  fscanf(fp, "%d%d%d", filas, columnas, tipo);

  if (((*tipo) != POR_COLUMNAS) && ((*tipo) != POR_FILAS))
    printf("Inconsistencia en argumento 4 en llamada a Load_Cabecera_Ascii\n");

  /* cerrar y fin */
  fclose(fp);
}

void Load_Bin(char *nombre_fichero, int filas, int columnas, int tipo, double *a) {
  /* Lee de un fichero binario una matriz/vector */
  /* Formato del fichero:                        */
  /*      filas  columnas TIPO                   */
  /*      dato_1 dato_2 ... dato_filas*columnas  */
  /* Significado de TIPO:                        */
  /*      0: almacenamiento por columnas         */
  /*      1: almacenamiento por filas            */
  FILE *fp;
  int tmp_filas=0, tmp_columnas=0, tmp_tipo=0;
  fp=fopen(nombre_fichero, "r");

  /* Lee cabecera */
  fread(&tmp_filas,    sizeof(int), 1, fp);
  fread(&tmp_columnas, sizeof(int), 1, fp);
  fread(&tmp_tipo,     sizeof(int), 1, fp);

  if ((tmp_filas==filas) && (tmp_columnas==columnas) && (tmp_tipo==tipo))
    /* Lee datos (matriz) */
    fread(a, (filas*columnas*sizeof(double)), 1, fp);
  else
    printf("Inconsistencia entre argumentos 1 al 3 y cabecera del fichero en llamada a Load_Bin\n");

  /* cerrar y fin */
  fclose(fp);
}

void Load_Cabecera_Bin(char *nombre_fichero, int *filas, int *columnas, int *tipo) {
  /* Lee la cabecera de un fichero binario que contiene una matriz/vector  */
  /* Formato del fichero:                                                  */
  /*      filas  columnas TIPO                                             */
  /* Significado de TIPO:                                                  */
  /*      0: almacenamiento por columnas                                   */
  /*      1: almacenamiento por filas                                      */
  FILE *fp;
  fp=fopen(nombre_fichero, "r");

  /* Lee cabecera */
  fread(filas,    sizeof(int), 1, fp);
  fread(columnas, sizeof(int), 1, fp);
  fread(tipo,     sizeof(int), 1, fp);

  if (((*tipo) != POR_COLUMNAS) && ((*tipo) != POR_FILAS))
    printf("Inconsistencia en argumento 4 en llamada a Load_Cabecera_Ascii\n");

  /* cerrar y fin */
  fclose(fp);
}

double Compara(const int filas, const int columnas, const int tipo, const double *a, const double *b) {
  /* Compara por filas (tipo=1) o columnas (tipo=0) dos matrices         */
  /* (si filas != 1 y columnas !=1) o vectores (si columnas o filas = 1) */
  int i, j;
  double maximo=.0;

  // Por Filas
  if (tipo == POR_FILAS) {
    for (j=0; j<filas; j++) {
      register int tmp=j*filas;
      for (i=0; i<columnas; i++) 
	maximo = max(maximo, dabs(a[tmp+i] - b[tmp+i]));
    }
  }
  else 
    // Por Columnas
    if (tipo == POR_COLUMNAS) {
      for (j=0; j<columnas; j++) {
	register int tmp=j*columnas;
	for (i=0; i<filas; i++) 
	  maximo = max(maximo, dabs(a[tmp+i] - b[tmp+i]));
      }
    }
    else
      printf("Inconsistencia en los argumentos en llamada a funcion Compara\n");
  return maximo;
}



void Imprime_Pantalla(const int filas, const int columnas, const int tipo, const double *a) {
  /* Imprime por pantalla una matriz (filas !=1 y columnas !=1) o vector */
  /* (filas o columnas =1) que ha sido almacenada/o por filas (tipo=1) o */
  /* columnas (tipo=0)                                                   */
  int i, j;

  // Por Filas
  if (tipo == POR_FILAS) {
    int tmp;
    for (i=0; i<filas; i++) {
      tmp=i*columnas;
      for (j=0;j<columnas; j++)
	printf("%f  ",a[tmp+j]);
      printf("\n");
    }
  }
  else 
    // Por Columnas
    if (tipo == POR_COLUMNAS) {
      for (i=0; i<filas; i++) {
	for (j=0;j<columnas; j++)
	  printf("%f  ",a[j*filas+i]);
	printf("\n");
      }
    }
    else
      printf("Inconsistencia en los argumentos en llamada a funcion Imprime_Pantalla\n");
}

void Imprime_Plana(const int filas, const int columnas, const double *a) {
  /* Imprime por pantalla los elementos de una matriz/vector de forma plana, */
  /* tal y como están almacenados (consecutivamente) en memoria              */
  int i;

  for (i=0; i<filas*columnas; i++)
    printf("%f  ",a[i]);
  printf("\n");
}

void Transpuesta(const int filas, const int columnas, const int tipo, const double* a, double* b) {
  /* Realiza la transpuesta de una matriz (filas !=1 y columnas !=1) o de un vector  */
  /* (filas o columnas = 1). Asume que "filas" y "columnas" son las filas y columnas */
  /* de la matriz fuente (a). Debe haber concordancia entre el par (filas, columnas) */
  /* del origen (a) y el par (columnas, filas) del detino (b). Esta funcion esta     */
  /* pensada para que el recorrido por los elementos del destino (b) sea sin saltos, */
  /* tanto si el almacenamiento es por columnas como por filas.                      */
  /* NOTA: EL TIPO DE ALMACENAMIENTO DEL RESULTADO (matriz (b)) SERA EL MISMO QUE EL */
  /*       DE LA MATRIZ ORIGEN (matriz (a))                                          */
  int i, j;

  // Por Filas
  if (tipo == POR_FILAS)
    for (i=0; i<columnas; i++) {
      int tmp=i*filas;
      for(j=0; j<filas; j++)
	b[tmp+j]=a[j*columnas+i];
    }
  else 
    // Por Columnas
    if (tipo == POR_COLUMNAS)
      for (i=0; i<filas; i++) {
	int tmp=i*columnas;
	for(j=0; j<columnas; j++)
	  b[tmp+j]=a[j*filas+i];
      }
    else
      printf("Inconsistencia en los argumentos en llamada a funcion Transpuesta\n");
}

void Rellena(const int filas, const int columnas, const int tipo, float *a) {
  /* Usa la funcion slarnv de LAPACK/ATLAS/MKL para rellenar aleatoriamente  */
  /* por filas (tipo=1) o columnas una matriz (tipo=0) o un vector (si filas */
  /* o columnas igual a 1).                                                  */

  int distribution_type = 3;
  /*         "          = 1 distribucion uniforme (0, 1)   */
  /*         "          = 2 distribucion uniforme (-1, -1) */
  /*         "          = 3 distribucion normal   (0, 1)   */
  int iseed[4];
  /* Vector de E/S con las semillas para el generador de aleatorios    */
  /* Sus valores debeb estar comprendidos entre 0 y 4095 y el elemento */
  /* de la ultima posicion (iseed[3]) debe ser impar                   */

  int i, tmp;

  tmp=(columnas + filas + (Primera_Vez_Alea*2)) % 4095;
  Primera_Vez_Alea++;
  if ((tmp % 2) == 0) tmp ++;
  iseed[0]=iseed[1]=iseed[2]=iseed[3]=tmp;

  // Por Filas
  if (tipo == POR_FILAS) {
    tmp=columnas;
    for (i=0; i<filas; i++)
      slarnv_(&distribution_type, iseed, &tmp, &a[i*columnas]);
  }
  else 
    if (tipo == POR_COLUMNAS) {
      tmp=filas;
      for (i=0; i<columnas; i++)
	slarnv_(&distribution_type, iseed, &tmp, &a[i*filas]);
    }
    else
      printf("Inconsistencia en los argumentos en llamada a funcion Rellena\n");
}

