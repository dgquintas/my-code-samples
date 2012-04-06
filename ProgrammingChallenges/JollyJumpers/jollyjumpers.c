#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int parseInput(int* v){
    int n;
    int got_input = (scanf("%d", &n) != EOF);
    if( got_input ){
        v[0] = n;
        int i;
        for(i=1; i <= n; i++){
            scanf("%d", &(v[i]));
        }
    }
    return got_input;
}

char table[3001];
int solve(int* v){
    bzero(table,sizeof(char)*3001);

    int n=v[0];

    int i, diff;

    for(i=1; i < n ; i++){
        diff = abs(v[i]-v[i+1]);
        if( table[diff] || (diff > n-1) || (diff < 1) ){
            return FALSE;
        }
        table[diff] = 1;
    }

    for(i=1; i < n; i++){
        if( table[i] == 0 ){
            return FALSE;
        }
    }

    return TRUE;
}

int main(){

    int v[3002];
    while( parseInput(v) ){
        if( solve(v) == TRUE ){
            printf("%s\n", "Jolly");
        }
        else{
            printf("%s\n", "Not jolly");
        }
    }
    return 0;
}



