#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

int main(){
  stringstream ss;

  double d = 1.123456789;
  double e = 0;

  ss << fixed << setprecision(16) <<d;

  ss >> e;

  cout  << fixed << setprecision(16) << e << endl;

  return 0;
}
