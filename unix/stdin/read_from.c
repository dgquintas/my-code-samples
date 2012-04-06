#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define BUFSIZE 1048576

int main(){

    char* buf = (char*)malloc(BUFSIZE);
    assert(buf);
    int br;
    while( (br=fread(buf, 1, BUFSIZE, stdin) ) ){
        printf("Read %d bytes\n", br);
    }
//    while( (br=read(0, buf, BUFSIZE) ) ){
//        printf("Read %d bytes\n", br);
//    }

    return 0;
}

