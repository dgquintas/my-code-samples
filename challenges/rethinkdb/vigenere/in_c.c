#include <stdio.h>
#include <string.h>

char num_to_alpha(int n){
    static const int ALPHABET_SIZE = 'z'-'a'+1;
    if( n < 0 ){  n += ALPHABET_SIZE; }
    return (char)(n + 'a');
}
int keyn(const char* const keytxt, int i){
    return keytxt[i] - '0';
}

int main(){
    int i;
    static const char* const keytxt = "61803398874";
    static const char* const ct = "xfbhlqtlj";

    for(i=0; i < strlen(ct); i++){
        printf("%c", num_to_alpha( (ct[i] - 'a') - keyn(keytxt,i) ));
    }
    printf("\n");
    
    return 0;
}
