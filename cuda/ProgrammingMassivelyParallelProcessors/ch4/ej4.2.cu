#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define X 8
#define Y 8 


#define GETCOORDS(row, col) (row) * (Y) + (col)
#define CEIL(x,y) (((x)-1) / (y)) + 1

std::string sprint(float *M){
    std::ostringstream oss;
    for( int i = 0; i < X; i++) {
        for( int j = 0; j < Y; j++) {
            oss << M[ GETCOORDS(i,j) ] << " " ;
        }
        oss << std::endl;
    }
    return oss.str();
}


__global__ void TransKernel(float* Md, int width){

    int bx = blockIdx.x;
    int by = blockIdx.y;

    int tx = threadIdx.x;
    int ty = threadIdx.y;

    __shared__ float block[BLOCK_SIZE][BLOCK_SIZE];
    
    int baseIdx = bx * BLOCK_SIZE + tx;
    baseIdx += (by * BLOCK_SIZE + ty) * width;

    block[ty][tx] = Md[baseIdx];
    Md[baseIdx] = block[tx][ty];

}

void MatrixTrans(float* M, int width){
    int size = width*width*sizeof(float);
    float *Md;

    //0. reserve memory on device
    cudaMalloc( (void**)&Md, size );

    //1. transfer M and N to device memory
    cudaMemcpy(Md, M, size, cudaMemcpyHostToDevice);

    //2. kernel invokation 
    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
    dim3 dimGrid(CEIL(width,BLOCK_SIZE), CEIL(width,BLOCK_SIZE));
    printf("Using (%d, %d) blocks of (%d, %d) threads each\n", dimGrid.x, dimGrid.y, dimBlock.x, dimBlock.y);   

    TransKernel<<<dimGrid, dimBlock>>>(Md, width);

    //3. copy P from device to host
    cudaMemcpy(M, Md, size, cudaMemcpyDeviceToHost);

    //4. Free Md, Nd, Pd
    cudaFree(Md);
}


int main(){
    float *M;

    // allocate M, N, P
    M = (float*)malloc( sizeof(float)*X*Y );

    int k=1;
    for( int i = 0; i < X; i++) {
        for( int j = 0; j < Y; j++) {
            M[ GETCOORDS(i,j) ] = k++;
        }
    }
    const std::string Ms(sprint(M));
    std::cout << Ms << std::endl;

    // M*N on device
    MatrixTrans(M, Y);
    
    const std::string res(sprint(M));
    std::cout << res << std::endl;

    // Free M, N, P
    free(M);

    return 0;
}
