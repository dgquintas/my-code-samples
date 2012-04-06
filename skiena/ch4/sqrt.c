#include <stdio.h>

/* The idea is to find the sqrt of a number by binary searching. 
 * We know that 0 < sqrt(n) < n. We take the midpoint as m = (ini+end)/2.
 * In order to test for a solution, we square the candidate m 
 * and compare it with n. If it's close enough, m will be the sqrt(n)
*/
float binSearch(float n, float ini, float end){
    float m = (ini+end)/2;
    float m2 = m*m;

    if( end <= ini ){
        return m;
    }
    if( m2 > n ){ //gotta select a smaller m
        return binSearch(n, ini, m);
    }
    else if( m2 < n ){ //gotta select a larger m
        return binSearch(n, m+0.000001, end);
    }
}
    

float _sqrt(float n){
    return binSearch(n, 0, n);
}

int main(){

    printf("%f\n", _sqrt(2));
    return 0;
}

