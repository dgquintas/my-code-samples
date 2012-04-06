class Foo{

  public:
    void operator()(int i, int j, int k, ... ) {}
    void operator()(int i, int j) {}
    void operator()(int i) {}

};


int main(){

  Foo foo ;

  foo(1,2,3,4,5);
  foo(1,2,3);
  foo(1,2);
  foo(1);

  return 0;
}
