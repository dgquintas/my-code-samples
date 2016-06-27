#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <cstdlib>

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

class C {};

int main() {
    using std::cout;
    using std::endl;
    cout << type_name<int>() << endl;
    cout << type_name<long int>() << endl;
    cout << type_name<long long>() << endl;
    cout << type_name<long double>() << endl;
    cout << type_name<C>() << endl;

    return 0;
}
