#include <iostream>

int main(){
  const int a =1;
  int const aa =2;

  int x[] = {1,2,3};
  int y[] = {3,2,1};
  int z = 4;

  const int* b = x;
  int* const bb = x;
  const int* const bbb = x;

  const int& c = z;

//  a = 2;   //fails
//  aa = 2;  //fails

//  b[0] = 2;  //fails
 bb[0] = 2;    //OK
//bbb[0] = 2;  //fails
 
  b = y; //OK
// bb = y; //fails
//bbb = y;  //fails

//  c = 5; //fails

  return 0;
}

