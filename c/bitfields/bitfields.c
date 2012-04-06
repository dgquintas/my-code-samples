#include <stdio.h>
#include <string.h>

struct test1 {
    unsigned int foo :4;
    unsigned int bar :4;

    unsigned char lol :1;
    unsigned short rofl :3;
    unsigned int anotherInt :8;
} ;

int main(){
    struct test1 t1;

    memset(&t1, 0, sizeof(t1));

    t1.foo = 0xA;
    t1.bar = 0xB;

    t1.lol = 1 ;

    t1.rofl = 7;
    t1.anotherInt = 0xDE;

    return 0;
}
