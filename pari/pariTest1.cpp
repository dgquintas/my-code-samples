#include <iostream>
#include <pari/pari.h>

using namespace std;

int main(){

  pari_init(1000000, 0);
  
  GEN x,r,m;

  x = gp_read_str("345636344343");
  m = gp_read_str("32027");

  r = gmod(x,m);
  printf("x %% m = %s\n", GENtostr( gp_read_str("345636344343 % 32027")));

  return 0;

}
