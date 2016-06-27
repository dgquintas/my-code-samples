#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <string>
#include <cstdlib>
#include "foo.h"

template <typename T>
std::string type_name() {
    int status;
    std::string tname = typeid(T).name();
    char *demangled_name =
        abi::__cxa_demangle(tname.c_str(), NULL, NULL, &status);
    if (status == 0) {
        tname = demangled_name;
        std::free(demangled_name);
    }
    return tname;
}

template <typename T>
void Foo<T>::DoStuff() {
    std::cout << "From .cpp for " << type_name<T>() << std::endl;
}

template class Foo<int>;
template class Foo<double>;
