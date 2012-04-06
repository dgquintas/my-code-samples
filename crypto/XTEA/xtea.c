/* from http://en.wikipedia.org/wiki/XTEA */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
 
/* take 64 bits of data in v[0] and v[1] and 128 bits of key in k[0] - k[3] */
 
void encipher(unsigned int num_rounds, uint32_t v[2], uint32_t const k[4]) {
    unsigned int i;
    uint32_t v0=v[0], v1=v[1], sum=0, delta=0x9E3779B9;
    for (i=0; i < num_rounds; i++) {
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
        sum += delta;
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum>>11) & 3]);
    }
    v[0]=v0; v[1]=v1;
}
 
void decipher(unsigned int num_rounds, uint32_t v[2], uint32_t const k[4]) {
    unsigned int i;
    uint32_t v0=v[0], v1=v[1], delta=0x9E3779B9, sum=delta*num_rounds;
    for (i=0; i < num_rounds; i++) {
        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum>>11) & 3]);
        sum -= delta;
        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
    }
    v[0]=v0; v[1]=v1;
}

int main(){

    char input[64] = "I'm a little teapot";
    char output[64];
    uint32_t crypt[16];
    char key[16] = "0123456789ABCDEF";
    
    int i;
    const n = strlen(input);
    uint32_t* inp = (uint32_t*)input;
    for(i=0; i < n/sizeof(uint32_t); i++){
        uint32_t vs[2];
        vs[0] = htonl(inp[0]);
        vs[1] = htonl(inp[1]);
        encipher(64, vs, (uint32_t const*)key);
        crypt[i] = vs[0];
        crypt[i+1] = vs[1];
        inp++;
    }
    printf("\n");
    inp = crypt;
    for(i=0; i < n/sizeof(uint32_t); i++){ 
        decipher(64, inp, (uint32_t const*)key);
        printf("0x%x 0x%x ", inp[0], inp[1]);
        inp++;
    }
    printf("\n" );



    return 0;
}
