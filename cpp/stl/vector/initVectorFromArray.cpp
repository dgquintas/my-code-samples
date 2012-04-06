#include <vector>
#include <iostream>


int main(){

  int array[] = {1,2,3};

  std::vector<int> v(array, array + sizeof(array) / sizeof(int) );

  for( int i=0; i < v.size(); i++){
    std::cout << v[i] << std::endl;
  }

  return 0;
}
