// This type of casting manipulates the constness of an object, either to be
// set or to be removed. For example, in order to pass a const argument to a
// function that expects a non-constant parameter:
#include <iostream>
using namespace std;

void print (char * str) {
  cout << str << endl;
}

int main () {
  const char* c = "sample text";
  //print ( c ); // this fails
  print ( const_cast<char *> (c) );
  return 0;
}
