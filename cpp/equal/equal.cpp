#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main(){

  vector<int> v1;
  vector<int> v2;

  v1.push_back(1);
  v1.push_back(2);
  v1.push_back(3);

  v2.push_back(1);
  v2.push_back(2);
  v2.push_back(3);
  v2.push_back(88);

  const vector<int> *mayor;
  const vector<int> *menor;

  if( v1.size() > v2.size() ){
    mayor = &v1;
    menor = &v2;
  }
  else{
    mayor = &v2;
    menor = &v1;
  }

  if( equal(menor->begin(), menor->end(), mayor->begin()) ){
    cout << "iguales" << endl;
  }
  else{
    cout << "dif" << endl;
  }

  return 0;
}

