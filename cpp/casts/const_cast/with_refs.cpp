// from http://publib.boulder.ibm.com/infocenter/macxhelp/v6v81/topic/com.ibm.vacpp6m.doc/language/ref/clrc05keyword_const_cast.htm#HDRKEYWORD_CONST_CAST
#include <iostream>
using namespace std;
 
void f(int* p) {
  cout << *p << endl;
}

void g(int& p) {
    cout << p << endl;
}
 
int main(void) {
  const int a = 10;
  const int* b = &a;
 
  // Function f() expects int*, not const int*
  //   f(b);
  int* c = const_cast<int*>(b);
  f(c);
 
  // Lvalue is const
  //  *b = 20;
 
  // Undefined behavior: asignando a lo que en realidad es una zona const, 
  // via primero const int* b pero en realidad y de forma ultima, const int a
  //  *c = 30;
 
  int a1 = 40;
  const int* b1 = &a1;
  int* c1 = const_cast<int*>(b1);
 
  // Integer a1, the object referred to by c1, has
  // not been declared const
  // asi que lo siguiente ahora SI es valido
  *c1 = 50;
 

  // ahora referencias
  const int aa = 123;
  // g(a); // esto peta
  int bb = const_cast<int&>(aa);
  g(bb);

  // y si la mierda esta no era const pa empezar?
  int aaa = 456;
  int bbb = const_cast<int&>(aaa);
  g(bbb);
  // pos na, bien XD

  return 0;

}
