#include <iostream>

class C {
    public:
        C() :
            a(0xdeadbabe), b(1.0) {}
        virtual void f(){}
        virtual void f2(){}
        void g(){}

    private:
        int a;
        float b;
};

typedef void (C::*F_PTR)();
int main() {

    C c;

    F_PTR f_p = &C::f;
    F_PTR g_p = &C::g;
    std::cout << sizeof(c) << std::endl;


    return 0;
}

