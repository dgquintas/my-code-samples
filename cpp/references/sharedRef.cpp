#include <vector>
#include <iostream>

int main(){
  std::vector<int> a;
  std::vector<int>& aRef(a);

  a.push_back(123);
  std::cout << a[0] << std::endl;
  aRef[0] = 321;
  std::cout << a[0] << std::endl;

  return 0;
}

