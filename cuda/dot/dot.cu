// simple stupid dot product example from chapter 5 of CUDA by Example
// as worked by myself from scratch

#include <stdio.h>

#define N 1000000

#define BPG 16
#define TPB 16


__global__ void dot(float *a, float *b, float *c){
    //accumulate thread result on shared mem (per block)
    __shared__ float cache[TPB];
    int tid = (blockDim.x * blockIdx.x) + threadIdx.x;
    float acum = 0;
    while( tid < N ){
        acum += a[tid] * b[tid];
        tid += gridDim.x * blockDim.x;
    }
    cache[ threadIdx.x ] = acum;

    //need to agregate the result for this block into 
    //a single scalar, from the individual thread results
    // for that, we must be sure all threads have finished
    //barrier here.
    __syncthreads();
    

    for(int i=blockDim.x/2; i > 0; i /= 2){
        tid = threadIdx.x;
        // because all threads are gonna go thru here anyway,
        // but only the i leftmost ones should do sth.
        if( tid < i ){ 
            cache[tid] += cache[tid + i];
        }
        __syncthreads(); // regroup before next iteration
    }

    //block's sum at cache[0]
    //somebody's gotta write it back to the host 
    if( threadIdx.x == 0 ){
        c[blockIdx.x] = cache[0];
    }

}

#define sum_squares(x) ((x*(x+1)*(2*x+1))/6)

int main(){
    float a[N], b[N], c[BPG];
    float *dev_a, *dev_b, *dev_c;

    cudaMalloc( (void**)&dev_a, N * sizeof(float) );
    cudaMalloc( (void**)&dev_b, N * sizeof(float) );
    cudaMalloc( (void**)&dev_c, BPG * sizeof(float) );

    for(int i=0; i < N; i++){
        a[i] = i;
        b[i] = 2*i;
    }

    cudaMemcpy( dev_a, a, N*sizeof(float), cudaMemcpyHostToDevice );
    cudaMemcpy( dev_b, b, N*sizeof(float), cudaMemcpyHostToDevice );

    dot<<<BPG, TPB>>>(dev_a, dev_b, dev_c);

    cudaMemcpy( c, dev_c, BPG*sizeof(float), cudaMemcpyDeviceToHost );


    //sum the results from the individual blocks
    float res=0;
    for(int i=0; i < BPG; i++){
        printf("c[%d] = %f\n", i, c[i]);
        res += c[i];
    }
    
    printf("Result: %f (vs. %f)\n", res, 2*sum_squares((float)(N-1)));


    cudaFree( dev_a );
    cudaFree( dev_b );
    cudaFree( dev_c );

    return 0;
}


