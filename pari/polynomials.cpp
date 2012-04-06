#include <iostream>
#include <pari/pari.h>

using namespace std;

int main(){

  pari_init(1000000, 0);
  
  GEN p = gp_read_str("4*x^3 + 6*x -1034875034820");
  GEN q = gp_read_str("4*x^2 + 3*x + 100");
  GEN ev = poleval(q,gp_read_str("1488"));
  cout << GENtostr(ev) << endl;
  GEN pq = gmul(p,q);
  printf("%d\n", degpol(pq) );
  for( int i = 0; i <= degpol(pq); i++){
    printf("%d -> %s\n", i, GENtostr((GEN)pq[i+2]) );
  }

  return 0;

}
