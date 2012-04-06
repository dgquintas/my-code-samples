#include <stdio.h>

float InvSqrt(float x)
{
  float xhalf = 0.5f*x;
  int i = *(int*)&x; // get bits for floating value
  i = 0x5f375a86- (i>>1); // gives initial guess y0
  x = *(float*)&i; // convert bits back to float
  x = x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
  return x;
}

int main(){
  float x;

  scanf("%f", &x);

  printf("%f\n", InvSqrt(x));

  return 0;
}
