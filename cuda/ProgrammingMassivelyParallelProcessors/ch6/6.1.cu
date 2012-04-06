#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define N (1<<22)
#define BLOCK_SIZE 128

static void HandleError( cudaError_t err,
                         const char *file,
                         int line ) {
    if (err != cudaSuccess) {
        printf( "%s in %s at line %d\n", cudaGetErrorString( err ),
                file, line );
        exit( EXIT_FAILURE );
    }
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))


#define HANDLE_NULL( a ) {if (a == NULL) { \
                            printf( "Host memory failed in %s at line %d\n", \
                                    __FILE__, __LINE__ ); \
                            exit( EXIT_FAILURE );}}

__global__ void reduxKernel(int* v, int n, int* res){
    int tx = threadIdx.x;
    int idx = blockIdx.x * (BLOCK_SIZE*2) + tx;
    __shared__ int vs[BLOCK_SIZE*2]; 
    
    // all threads execute the following, as the size of the shared memory is 
    // 2x the number of threads
    int reg = idx < n ? v[idx] : 0;
    if( idx + BLOCK_SIZE < n ){
        reg += v[idx + BLOCK_SIZE];
    }

    //vs[tx] = v[idx] + v[idx + BLOCK_SIZE];
    vs[tx] = reg;
    __syncthreads();

    if( BLOCK_SIZE >= 512 ){
        if( tx < 256 ){ vs[tx] = reg = reg + vs[tx + 256]; __syncthreads(); }
    } 
    if( BLOCK_SIZE >= 256 ){
        if( tx < 128 ){ vs[tx] = reg = reg + vs[tx + 128]; __syncthreads(); }
    }
    if( BLOCK_SIZE >= 128 ){
        if( tx < 64 ){ vs[tx] = reg = reg + vs[tx + 64]; __syncthreads(); }
    }
//    for( int bs = BLOCK_SIZE/2 ; bs > 32; bs >>= 1 ){
//        if( tx < bs ){
//            //accumulating on the register var "reg" saves a read
//            //from shared memory. Instead of doing vs[tx] += vs[tx + bs], 
//            //we just accum on the reg and write it back to shared memory
//            vs[tx] = reg = reg + vs[tx + bs];
//        }
//        __syncthreads();
//    }

    if( tx < 32 ){ //for the last wrap. Threads within a wrap don't need synchronize
        volatile int* synchdShared = vs; //so that the compiler doesn't reorder

        // in case the block size were less than 32 to begin with
        if( BLOCK_SIZE  >= 64 ){
            // means we can "reach out" fully 32 positions to the right of the thread
            // look at the general loop to work out why
            synchdShared[tx] = reg = reg + synchdShared[tx + 32];
        }
        //and of course we are gonna fall-through
        if( BLOCK_SIZE >= 32 ){ 
            synchdShared[tx] = reg = reg + synchdShared[tx + 16];
        }
        if( BLOCK_SIZE >= 16 ){
            synchdShared[tx] = reg = reg + synchdShared[tx + 8];
        }
        if( BLOCK_SIZE >= 8 ){
            synchdShared[tx] = reg = reg + synchdShared[tx + 4];
        }
        if( BLOCK_SIZE >= 4 ){
            synchdShared[tx] = reg = reg + synchdShared[tx + 2];
        }
        if( BLOCK_SIZE >= 2 ){
            synchdShared[tx] = reg = reg + synchdShared[tx + 1];
        }

    }

    //interesting: without this if, the kernel execution takes 5x the time! Probably
    //due the memory conflicts created by _ALL_ the threads trying to write to the same
    //memory location "at once"
    if(tx == 0){ 
       res[blockIdx.x] = vs[0];
    }

}

int hostRedux(int* v, int n){
    int res = 0;
    for(int i=0; i < n; i++){
        res += v[i];
    }
    return res;
}

void deviceRedux(int* v, int n, int* res){
    // reserve memory on device
    int *vd; 
    int *resd;
 
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    float time; 

    const int numBlocks = (N/BLOCK_SIZE)/2;

    HANDLE_ERROR( cudaMalloc((void**)&vd, n*sizeof(int)) );
    HANDLE_ERROR( cudaMalloc((void**)&resd, numBlocks*sizeof(int)) );

    cudaEventRecord( start, 0 ); 
    // transfer v to vd
    HANDLE_ERROR( cudaMemcpy(vd, v, n*sizeof(int), cudaMemcpyHostToDevice) );
    cudaEventRecord( stop, 0 );
    
    cudaEventSynchronize( stop );
    cudaEventElapsedTime( &time, start, stop );
    printf("memcpy in time: %f ms\n", time);

 
    cudaEventRecord( start, 0 );
    // invoke kernel
    reduxKernel<<<numBlocks,BLOCK_SIZE>>>(vd,n,resd);
    cudaEventRecord( stop, 0 );
    
    cudaEventSynchronize( stop );

    cudaEventElapsedTime( &time, start, stop );

    printf("kernel time: %f ms. ", time);
    printf("Bandwidth: %f GB/s\n", (N*sizeof(int)/1e6)/time);

    cudaEventRecord( start, 0 );  
    // copy results back to host
    HANDLE_ERROR( cudaMemcpy(res, resd, numBlocks*sizeof(int), cudaMemcpyDeviceToHost) );
    cudaEventRecord( stop, 0 );
    
    cudaEventSynchronize( stop );
    cudaEventElapsedTime( &time, start, stop );
    printf("memcpy out time: %f ms\n", time);
 
 
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    //free vd
    cudaFree(vd);
    cudaFree(resd);
}

     /* Subtract the `struct timeval' values X and Y,
        storing the result in RESULT.
        Return 1 if the difference is negative, otherwise 0.  */
     
int
timeval_subtract (struct timeval* result, struct timeval*x, struct timeval*y)
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }

  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}


int main(){
    int* v = (int*)malloc( sizeof(int) * N);
    for(int i=0; i < N; i++){
        v[i] = rand() % 10;
        //v[i] =  i;
    }

    int h;
    struct timeval tv_start;
    struct timeval tv_stop;
    struct timeval tv_diff;
    gettimeofday(&tv_start, 0);
    h=hostRedux(v,N);
    gettimeofday(&tv_stop, 0);
    timeval_subtract(&tv_diff, &tv_stop, &tv_start);
    printf("host: %d\n", h);
    float msdiff = tv_diff.tv_sec*1000 + tv_diff.tv_usec/1000.0;
    printf("CPU time: %.3f ms\n", msdiff);

    const int numBlocks = (N/BLOCK_SIZE)/2;
    int *res = (int*)malloc( sizeof(int) * numBlocks);
    int d;

    cudaEvent_t start, stop;
    float time; 
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord( start, 0 );

    deviceRedux(v,N, res);
    d=0;
    for(int i=0; i < numBlocks; i++){
       // printf("%d\n", res[i]);
        d+=res[i];
    }
    cudaEventRecord( stop, 0 );
    cudaEventSynchronize( stop );

    cudaEventElapsedTime( &time, start, stop );
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    printf("CUDA time: %f ms\n", time);


    printf("device: %d\n", d);

    free(v);
    free(res);
    return !(h==d);

}
