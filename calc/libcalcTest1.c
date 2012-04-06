#include <calc/zmath.h>
#include <stdio.h>

void libcalc_call_me_first();

int main()
{
  ZVALUE z1, m, res;
  char str[1024];

  libcalc_call_me_first();

  scanf("%s", str);
  str2z(str, &z1);
  scanf("%s", str);
  str2z(str, &m);

  zmod(z1, m, &res, 0);

  zprintval(res, 0,0);
  
  return 0;
}


