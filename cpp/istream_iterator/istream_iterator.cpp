#include <iostream>
#include <iterator>

using namespace std;

int main(){

  istream_iterator<char> it;
  const istream_iterator<char> end = istream_iterator<char>();

  for(it = istream_iterator<char>(cin); it != end; it++ ){
    cout << *it << " ";
  }
  cout << endl;

  return 0;
}
