#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "hmac.h"
#include "base32.h"

int is_big_endian(void) {
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1; 
}

void change_endianness64(uint64_t* pi){
    register uint64_t i = *pi;
    // swap 32 bit words
    i = (i << 32) | (i >> 32);
    // swap 16 bit words
    uint64_t m = 0xffff0000ffff0000;
    i = ((i & m) >> 16) | ((i & ~m) << 16);
    // swap bytes
    m = 0xff00ff00ff00ff00;
    i = ((i & m) >> 8) | ((i & ~m) << 8);
    *pi = i;
}


uint32_t HOTP(const uint8_t* key, int keyLength, uint64_t counter){
    // we need to transform C into a 8-byte array
    // we naturally need to determine the endianness of the system
    if( !is_big_endian() ){
        change_endianness64(&counter);
    }
    uint8_t HS[20];
    hmac_sha1(key, keyLength, (const uint8_t*)&counter, 8, HS, 20);
    int offset = HS[19] & 0xf;

    // we now want the 31 lsb's of the 32 bit dword starting at byte "offset"
    // of HS
    uint8_t* offsetHS = HS + offset;
    uint32_t p;
    if( is_big_endian() ){
        memcpy(&p, offsetHS, 4);
    }
    else{
        p = *(offsetHS+3);
        p |= *(offsetHS+2) << 8;
        p |= *(offsetHS+1) << 16;
        p |= *(offsetHS)   << 24;
    }

    p &= 0x7fffffff;
    // now get only the least significant 6 decimal digits
    p %= 1000000;

    return p;
}

int main(){
    const char* keyb32 = "wa2oatxr5y65iugt";
    uint8_t key[20];
    base32_decode((const uint8_t*)keyb32, key, 20);

    const int X = 30;
    const int c = time(NULL) / X;

    printf("%d\n", HOTP(key, 20, c));
    return 0;
}

