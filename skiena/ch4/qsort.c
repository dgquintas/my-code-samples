#include <stdlib.h>
#include <stdio.h>

void swap(int* pi, int* pj){
    int tmp = *pi;
    *pi = *pj;
    *pj = tmp;
}


/* Returns the position for the pivot p, randomly chosen,
 * so that every element to its left is < v[p] and
 * every element to its right it's >= v[p]
 *
 * Invariant: v[ini..eviction_ptr] < v[p]
 *            v[eviction_ptr..i] >= v[p]
 *            v[i..end] unexplored
 *
 * Post-cond: v[ini..p-1] < v[p]
 *            v[p..end] >= v[p]
 */
int partition(int* v, int ini, int end){
    int n = end - ini;

    //chose the pivot. REMEMBER TO ADD INI TO IT!
    int p = ini+(rand() % n);
    int pivot = v[p];
    /* we retrieve and store its value. This is so
     * because we are dealing with a random element
     * instead of, for example, always consider the last
     * position of the slice. 
     * If we just worked with v[p], it may happen that
     * eviction_ptr eventually points at it and the very
     * pivot gets moved around, thus fucking everything up.
     *
     * To avoid that, we simply swap v[p] with the last element
     * of the array. This way we get it "out of the way" while 
     * still considering its value for all the comparisons.
     * This way, we know that eviction_ptr won't get to point to
     * it as long as there are elements larger than it. The only
     * case in which it'd point at it would be if v[p] is actually
     * the largest. Then, it'd just swap with itself. no biggie.
     *
     * At the end, we simply swap this last position with 
     * v[eviction_ptr], which is where the value would go. The 
     * value at v[eviction_ptr] is >= than v[p], so it's cool if
     * it goes to the last position, as that fulfills the postcondition.
     */
    swap( &v[p], &v[end-1] );
    int i; 

    // the following will hold the index of an element potentially
    // larger than v[p] and thus candidate to be exchanged for a 
    // posterior element (pointed by the usual iterator index i) 
    // that's < v[p]
    // This pointer only advances after an actual swap has occurred. 
    int eviction_ptr = ini; 
    for(i = ini; i < end; i++){
        if( v[i] < pivot ){
            swap( &v[eviction_ptr], &v[i] );
            ++eviction_ptr;
        }
    }
    //at this point, eviction_ptr points to the "leftmost" element
    // >= v[p]. Everything to its right will be so too. 
    // Exchange it with v[p] to fulfill the post-condition.
    swap( &v[eviction_ptr], &v[end-1] );

    return eviction_ptr;
}

void quicksort(int *v, int ini, int end){

    if( end > ini ){
        int p = partition(v, ini, end);

        // v has changed now. to the left of its p-th position, 
        // stuff is < v[p]. >= v[p] to its right.
        // v[p] won't move again

        // left chunck
        quicksort(v, ini, p);

        // right chunck. +1 is added because the pivot MUST BE 
        // LEFT ALONE. It's already at its final position
        quicksort(v, p+1, end);
    }
}

void print(int* v, int n){
    int i;
    for(i=0; i < n; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

#define N 20

int main(){
    int v[N];
    int i;
    for(i=0; i < N; i++){
        v[i] = rand() % 20;
    }
    print(v,N);

    quicksort(v, 0, N);
    print(v,N);
    return 0;
}


