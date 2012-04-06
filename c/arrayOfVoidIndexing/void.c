#include <stdio.h>


int main(){
  double d[] = {1.1, 2.2, 3.3};
  int i[] = {1,2,3};

  int dd = sizeof(double);
  int di = sizeof(int);

  char* data = (char*)&i;
  char* data2 = (char*)&d;
  
  int j;
  for(j = 0 ; j < 3; j++ ){
    printf("%d ", *(data+(j*di)));
  }
  printf("\n"); 
  for(j = 0 ; j < 3; j++ ){
    printf("%f ", *((double*)(data2+(j*dd))));
  }
  printf("\n");


  return 0;
}

