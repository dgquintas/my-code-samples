#include <iostream>

using namespace std;

class ABC{
  public: 
    virtual void foo() const = 0 ;
};

//class A;
//int onlyAs(const A& a);

class A : public ABC{

  public:
    virtual void foo() const ;
    // it's got the same acess privileges as any other method
    friend int onlyAs(const A&);
  private:
    int _foo;
};
void A::foo() const { 
  cout << "foo @ A" << endl; 
  onlyAs(*this);
}
int onlyAs(const A& a){
    //accessing a private member of A
  int x = a._foo +1;
  cout << "x = " << x << endl; 
  return x;
}



class B : public A
{
  public:
    virtual void foo() const ;
};
void B::foo() const{ 
  cout << "foo @ B" << endl; 
}




const ABC& func(const ABC& a){
  a.foo();
  return a;
}

int main(){
  A a;
  B b;

  func(a);
  func(b);

  return 0;
}

