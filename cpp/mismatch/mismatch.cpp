#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main(){

  vector<int> a;
  vector<int> b;

  a.push_back(123456);
  b.push_back(123456);

  typedef vector<int>::const_reverse_iterator It ;
  std::pair<It, It> p = mismatch(a.rbegin(), a.rend(), b.rbegin());
  if(*(p.first) < *(p.second)){
    cout << "<" << endl; 
  }else{
    cout << ">=" << endl;
  }

  return 0;
}
