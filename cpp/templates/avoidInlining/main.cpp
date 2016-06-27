#include "foo.h"

int main() {
    Foo<int> f(1);
    Foo<double> g(1.1);
    Foo<float> h(1.1);

    f.DoStuff();
    g.DoStuff();
    h.DoStuff(); // this will fail because Foo<float> hasn't been defined.
    // see www.parashift.com/c++-faq-lite/separate-template-class-defn-from-decl.html
}
