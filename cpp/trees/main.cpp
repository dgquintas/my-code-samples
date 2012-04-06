#include "tree.h"
#include <string>
#include <iostream>

int main(){
    Tree<int, std::string> t;

    t.add(1, "foo");
    t.add(2, "bar");
    t.add(0, "lol");

    return 0;
}

