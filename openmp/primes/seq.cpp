#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(){
  int max;
  cin >> max;

  vector<int> primes;
  primes.reserve(100);
  primes.push_back(2);

  for(int i = 3; i < max; i++ ){
    bool prime = true;
    for(vector<int>::iterator it = primes.begin(); it != primes.end(); it++){
      if( (*it)*(*it) > i ){
        break;
      }
      if( ((i % (*it)) == 0) ){
        prime = false;
      }
    }
    if(prime){
      primes.push_back(i);
    }
  }


  for(vector<int>::iterator it = primes.begin(); it != primes.end(); it++){
    cout << (*it) << " " ;
  }
  cout << endl;

  return 0;
}





