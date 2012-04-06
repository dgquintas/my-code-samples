#include <iostream>
#include <gmpxx.h>

int main(){
    mpf_class f1(1, 1000);
    f1 /= 7;

    gmp_printf( "%.Ff\n", f1.get_mpf_t());
    return 0;
}
