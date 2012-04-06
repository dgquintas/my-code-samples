#include <iostream>

class B {
  public:
    virtual B foo() {return *this;};
  protected:
    B() : b_proct(123), b_priv(111) {};
    int b_proct;
  private:
    int b_priv;
};

class DB : private B {

    public:
        virtual B foo() {
            // we can access the base class' protected attributes
            int x = this->b_proct + 1;
            //int y = this->b_priv + 1; // can't do. 
            return *this;
        };
        void bar() {
        }
} ;

class D : public B{
};

int main(){
  DB db;
  D d;

  return 0;
}
