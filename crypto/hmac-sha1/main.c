#include <stdint.h>
#include <string.h>
#include <stdio.h>

int main(){
    uint8_t res[20];
    const uint8_t* key = "Jefe";
    const uint8_t* data = "what do ya want for nothing?";
    if(hmac_sha1(key, strlen(key), data, strlen(data), res)){
        fprintf(stderr, "woops\n");
    }
    else{
        char res_str[41];
        char hexbyte[3];
        int i;
        printf("Res:\n");
        res_str[0] = '\0';
        for(i=0; i<20; i++){
            snprintf(hexbyte, 3, "%x", res[i]);
            strcat(res_str, hexbyte);
        }
        printf("0x%s\n", res_str);
        printf("\n");
    }
    return 0;
}
