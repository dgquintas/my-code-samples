#include <iostream>

using namespace std;
extern unsigned long long int __get_clockfreq(void);
int main()
{
  cout << __get_clockfreq() << endl;

  return 0;
}
