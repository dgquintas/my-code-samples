#include <iostream>

using namespace std;

class clazz
{
  public:
    clazz(){
      cout << "construyendo " << this << endl;
    }
    ~clazz(){
      cout << "destruyendo " << this << endl;
    }
};


void func(){
  static clazz x;
  clazz y;
}


int main(){

  func();
  func();

  return 0;
}


