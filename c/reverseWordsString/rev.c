#include <stdio.h>
#include <string.h>

void swap(char* a, char* b){
    (*a) ^= (*b);
    (*b) ^= (*a);
    (*a) ^= (*b);
}

void reverse(char* str, int ini, int end){
    int i;
    int n = end-ini;
    str += ini;
    for(i=0; i < n/2; i++){
        swap( str+i, str+(n-1)-i );
    }
}

int main(){

    char str[] = "Morbi leo risus porta ac consectetur ac vestibulum at eros";
    printf("%s\n", str);
    int n = strlen(str);
    int i,j;

    //reverse string byte-wise
    reverse(str, 0,n);
    printf("%s\n", str);

    //detect and reverse individual words
    int ini = 0;
    for(i=0; i<n; i++){
        if( str[i] == ' ' ){
            reverse(str, ini, i);
            ini = i+1;
        }
        else if( i == n-1 ){ // end of the string
            reverse(str, ini, i+1); // i+1 because we want to include the last letter
        }
    }
    printf("%s\n", str);



    return 0;
}


