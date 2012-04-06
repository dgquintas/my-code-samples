#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void merge(int* v, int ini, int middle, int end){
    /*
     * Precondition: v[ini..middle] ordered w.r.t. each other
     *               v[middle+1..end] idem
     *
     * We need auxiliary space, not to overwrite the source values
     * while merging. For instance, if we had {4,5,6} and {1,2,3} and
     * we tried to merge in place, the 1 would smash the 4, the latter being
     * hence lost forevah.
     *
     * Let's modify v. We copy v[ini..middle] to left[] and 
     * v[middle+1..end] to right[]
     */
    int leftSize = middle-ini;
    int rightSize = end-middle;
    int* left = (int*)malloc(sizeof(int)*leftSize);
    int* right = (int*)malloc(sizeof(int)*rightSize);

    v += ini;
    memcpy(left, v, leftSize*sizeof(int));
    memcpy(right, v+leftSize, rightSize*sizeof(int));

    int i,j,k;
    i = j = k = 0;
    while( i < leftSize && j < rightSize){
        v[k++] = left[i] < right[j] ? left[i++] : right[j++];
    }
    while(j < rightSize){
        v[k++] = right[j++];
    }
    while(i < leftSize){
        v[k++] = left[i++];
    }

    free(left);
    free(right);
}

void msort(int* v, int ini, int end){
/* The idea is to have a recursive procedure that splits the input in halves, 
 * with the array of length 1 as the base case. 
 */
    int middle;
    int n = end-ini; //end is NOT included as a possible index [ini, end)
    if( n > 1 ){
        middle = ini + n/2; //this is better than (ini+end)/2, as it avoid overflows

        //the following will -we assume- modify v so that its first half is sorted
        msort(v, ini, middle);
        //ditto for the second half
        msort(v, middle, end);

        //now, to put together a final result, we have to merge both pieces
        merge(v, ini, middle, end);
    }
}

void print(int* v, int n){
    int i;
    for(i=0; i < n; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

#define N 17

int main(){
    int v[N];
    int i;
    for(i=0; i < N; i++){
        v[i] = rand() % 20;
    }
    print(v,N);

    msort(v, 0, N);
    print(v,N);
    return 0;
}


