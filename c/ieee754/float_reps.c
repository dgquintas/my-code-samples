#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>

int main(){
    int i;
    float f_arr[] = {1.0, 3.0, 0.0, INFINITY, NAN, FLT_EPSILON, FLT_MIN, FLT_MAX};
    double d_arr[]= {1.0, 3.0, 0.0, INFINITY, NAN, DBL_EPSILON, DBL_MIN, DBL_MAX};
    float f;
    double d;

    printf("%s\n", "FLOATS");
    for(i=0; i < 8; i++){
        f = f_arr[i];
        int as_int = *((int*)&f);
        printf("%g\n", f);
        printf("%#x\n", as_int);

        int sign, exp, mantissa;
        mantissa = as_int & ((1<<23)-1);
        as_int >>= 23;
        exp = as_int & ((1<<8)-1);
        as_int >>= 8;
        sign = as_int;
        printf("Sign: %d\n", sign);
        printf("Exp: %#0x\n", exp);
        printf("Mantissa: %#0x\n", mantissa);
        printf("\n");
    }   

    printf("%s\n", "DOUBLES");
    for(i=0; i < 8; i++){
        d = d_arr[i];
        long as_int = *((long*)&d);
        printf("%g\n", d);
        printf("%#lx\n", as_int);

        int sign, exp;
        long mantissa;
        mantissa = as_int & ((1L<<52)-1);
        as_int >>= 52;
        exp = as_int & ((1<<11)-1);
        as_int >>= 11;
        sign = as_int;
        printf("Sign: %d\n", sign);
        printf("Exp: %#0x\n", exp);
        printf("Mantissa: %#0lx\n", mantissa);
        printf("\n");
    }   

    return 0;
}

