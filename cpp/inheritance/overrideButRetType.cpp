class B{
  static int foo(){ return 1; }
};

class D : public B{
  static float foo() { return 1.1; };
};

int main() {

  D d;

  return 0;
}

