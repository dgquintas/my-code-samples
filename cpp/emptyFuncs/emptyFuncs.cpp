#include <cmath>

void empty(){};

double non_empty() { return sqrt(123); }

int main(){

  empty();

  double x=  non_empty();

  return (int)x;

}
