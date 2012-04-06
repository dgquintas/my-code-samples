#include <string>
#include <iostream>

using namespace std;

int main(){

  string str("[a b;c d]");
  string::size_type pos = str.find(' ');
  if( pos != string::npos ){
    do{
      str.replace(pos, 1, 1, ',');
      pos = str.find(' ', pos);
    } while( pos < str.size() );
  }

  cout << str << endl;

  return 0;
}
