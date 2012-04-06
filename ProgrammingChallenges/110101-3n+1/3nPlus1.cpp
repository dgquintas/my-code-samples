#include <iostream>
#include <cstring>

#define MAX 1000000

int getCycleLength(int* prevs, int n){
    int l = 1;
    while(n != 1){
        if( n & 0x1 ){
            // n is odd.  
            n = (n*3+1);
        }
        else{
            // n is even
            n >>= 1;
        }
        if( n < MAX && prevs[n] ){
            return l+prevs[n];
        }
        l++;
    }
    return l;
}


int main(){
    int i,j;
    while(std::cin >> i >> j){

        int prevs[MAX];
        bzero(prevs, MAX * sizeof(int));

        int max = -1;
        bool swapped = false;
        if( j <= i ){
            int tmp = i;
            i = j;
            j = tmp;
            swapped = true;
        }
        for(int n=i; n <= j; n++){
            const int res = getCycleLength(prevs, n);
            prevs[n] = res;
            if( res > max ) max = res;
        }
        if( swapped ){
            int tmp = i;
            i = j;
            j = tmp;
        }
        std::cout << i << " " << j << " " << max << std::endl;
    }

    return 0;
}
