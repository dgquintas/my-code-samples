#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <gmp.h>

float trivialSum(float* input, size_t n){
    int i;
    float sum = 0.0f;
    for(i=0; i < n; i++){
        sum += input[i];
    }
    return sum;
}

char* mpSum(float* input, size_t n){
    int i;
    char* resStr = (char*)malloc(1024);
    char* tmp = (char*)malloc(1024);
    mpf_t sum; mpf_init(sum);
    mpf_t in; mpf_init(in);
    for(i=0; i < n; i++){
        mpf_set_d(in, (float)input[i]);
        mpf_add(sum, sum, in);
    }
    mp_exp_t exp;
    mpf_get_str(tmp, &exp, 10, 1022, sum);
    strncpy(resStr, tmp, exp); resStr[exp]='.'; strcpy(resStr+exp+1, tmp+exp);
    
    free(tmp);
    return resStr;
}


float kahanSum(float* input, size_t n){
    float sum = 0.0f;
    float c = 0.0f; //compensation
    int i;
    for(i=0; i < n; i++){
        //incorporate the accrued compensation 
        float y = input[i] - c;
        
        // sum is big, y is small -> low order bits of y lots
        float t = sum + y; 

        // (t-sum) recovers high order bits. Algebraically, that'd be ( (sum + y) - sum
        // == y ). By substracting "y", we recover/discover which low order bits were
        // lost at "t = sum + y". Note that the recovered low part of "y" will be
        // negative!
        c = (t - sum) - y; 

        sum = t;
    }
    return sum;
}

float pairwiseSum(float* input, size_t n){
    // split input in pairs and reduce recursively
    float sum;
    int i;
    if( n <= 32 ){
        sum = 0.0f;
        for( i=0; i < n; i++ ){
            sum += input[i];
        }
    }
    else{
        size_t nn = n / 2;
        sum = pairwiseSum(input, nn) + pairwiseSum(input+nn, nn+(n&0x1));
    }
    return sum;
}

void printTime(char* out, clock_t t0, clock_t t1, int iters){
    clock_t diff = t1-t0;
    float secsPerIters = (diff/(float)CLOCKS_PER_SEC)/iters;
    sprintf(out, "%f secs for %d iters. %f iters per sec", secsPerIters, iters, 1/secsPerIters);
}
    


#define N 1000000

int main(){
    srand( time(NULL) );
    int i;
    float* v = (float*)malloc(N * sizeof(float));

    for(i=0; i < N; i++){
        v[i] = rand() / (float)RAND_MAX;
    }

//    for(i=0; i < N; i++){
//        printf("%f ", v[i]);
//    }
//    printf("\n", v[i]);

    clock_t t0, t1;

    float resTrivial, resKahan, resPairwise;
    char* exact;
    char times[128];
    const int ITERS = 100;

    t0 = clock(); for(i=0;i<ITERS;i++) resTrivial = trivialSum(v, N); t1 = clock();
    printTime(times, t0, t1, ITERS);
    printf("Trivial: %s\n", times);

    t0 = clock(); for(i=0;i<ITERS;i++)resPairwise = pairwiseSum(v, N); t1 = clock();
    printTime(times, t0, t1, ITERS);
    printf("Pairwise: %s\n", times);

    t0 = clock(); for(i=0;i<ITERS;i++)resKahan = kahanSum(v, N); t1 = clock(); 
    printTime(times, t0, t1, ITERS);
    printf("Kahan: %s\n", times);

    exact = mpSum(v, N);

    printf("Trivial:\t %.32f\n", resTrivial);
    printf("Pairwise:\t %.32f\n", resPairwise);
    printf("Kahan:\t\t %.32f\n", resKahan);
    printf("MP:\t\t %s\n", exact);

    free(v);
    free(exact);
    return 0;
}
