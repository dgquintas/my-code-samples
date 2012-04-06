#include <iostream>

using namespace std;

int main(){

  int x;
  char c;

  while( cin >> x )
    cout << x << endl;

  if( !cin.good() ) {
    cout << "KELOOOO" << endl;
  }
  cin.clear();
  c = cin.get();
  cout << c << endl;

  if( !cin.good() ) 
    cout << "LOL" << endl;


  return 0;

}
