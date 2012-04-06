template<typename T>
class A {};

template<typename T>
class B : public A<int> {
  B& operator+=(const B& rhs){ return *this; }
};

class C : public A<float> {};


void f(B<double> arg){};
void g(A<int> arg){};
void h(A<double> arg){};

int main(){

  B<float> b1;
  B<double> b2;

  C c;

//  f(b1);         ERROR
  f(b2);
  g(b1);
  g(b2);
//  g(c);          ERROR
//  h(b2);         ERROR

  return 0;
}
