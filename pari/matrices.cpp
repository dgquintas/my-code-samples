#include <iostream>
#include <pari/pari.h>
#include <cassert>

using namespace std;

int main(){

  pari_init(1000000, 0);
  
  GEN x,r,m;

  x = gp_read_str("83");
  m = zeromatcopy(4,4);
  for(int i = 1; i <= 4 ; i++)
    for(int j = 1; j <= 4 ; j++)
      gcoeff(m,i,j) = x;

  for(int i = 1; i <= 4 ; i++)
    for(int j = 1; j <= 4 ; j++)
      assert( cmpii( gcoeff(m,i,j), x) == 0 );
      
  r = gmul(m,m);

  printf("%s\n", GENtostr( m ));
  printf("%s\n", GENtostr( r ));

  return 0;

}
