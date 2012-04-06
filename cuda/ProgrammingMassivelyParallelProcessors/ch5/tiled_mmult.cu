#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define X 1600
#define Y 1600

#define BLOCK_SIZE_X 16
#define BLOCK_SIZE_Y 16

#define TILE_WIDTH 16

#define GETCOORDS(row, col) (row) * (Y) + (col)
#define CEIL(x,y) (((x)-1) / (y)) + 1

void MatrixMultHost(float* M, float* N, float* P, int width){
    for(int i=0; i < width; i++){
        for(int j=0; j < width; j++){
           float sum = 0;
           for(int k = 0; k < width; k++){
               sum += M[ GETCOORDS(i,k) ] * N[ GETCOORDS(k,j) ];
           }
           P[ GETCOORDS(i,j) ] = sum;
        }
    } 
}

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


__global__ void MatrixMulKernel(float* Md, float* Nd, float* Pd, int width){

    int bx = blockIdx.x;
    int by = blockIdx.y;

    int tx = threadIdx.x;
    int ty = threadIdx.y;

    __shared__ float Mds[TILE_WIDTH][TILE_WIDTH];
    __shared__ float Nds[TILE_WIDTH][TILE_WIDTH];

    int row = by * BLOCK_SIZE_Y + ty;
    int col = bx * BLOCK_SIZE_X + tx;
    if( row >= width || col >= width ) return;

    float res = 0.0f;
    for(int p=0; p < width/TILE_WIDTH; p++){
        Mds[ty][tx] = Md[row*width + (tx + p*TILE_WIDTH)];
        Nds[ty][tx] = Nd[(p*TILE_WIDTH + ty)*width + col ];
        __syncthreads();


        //dot product from shared memory
        for(int k=0; k < TILE_WIDTH; k++){
            res += Mds[ty][k] * Nds[k][tx];
        }  
        __syncthreads();
    }

    Pd[row*width + col] = res;

}

void MatrixMultDevice(float* M, float* N, float* P, int width){
    int size = width*width*sizeof(float);
    float *Md, *Nd, *Pd;

    //0. reserve memory on device
    cudaMalloc( (void**)&Md, size );
    cudaMalloc( (void**)&Nd, size );
    cudaMalloc( (void**)&Pd, size );

    //1. transfer M and N to device memory
    cudaMemcpy(Md, M, size, cudaMemcpyHostToDevice);
    cudaMemcpy(Nd, N, size, cudaMemcpyHostToDevice);

    cudaMemset(Pd, 0, size);

    //2. kernel invokation 
    dim3 dimBlock(BLOCK_SIZE_X, BLOCK_SIZE_Y);
    dim3 dimGrid(CEIL(width,BLOCK_SIZE_X), CEIL(width,BLOCK_SIZE_Y));
    printf("Using (%d, %d) blocks of (%d, %d) threads each\n", dimGrid.x, dimGrid.y, dimBlock.x, dimBlock.y);   

    MatrixMulKernel<<<dimGrid, dimBlock>>>(Md, Nd, Pd, width);

    //3. copy P from device to host
    cudaMemcpy(P, Pd, size, cudaMemcpyDeviceToHost);

    //4. Free Md, Nd, Pd
    cudaFree(Md);
    cudaFree(Nd);
    cudaFree(Pd);
}


int main(){
    srand(time(NULL));
    float *M, *N, *P;

    // allocate M, N, P
    M = (float*)malloc( sizeof(float)*X*Y );
    N = (float*)malloc( sizeof(float)*X*Y );
    P = (float*)malloc( sizeof(float)*X*Y );

    for( int i = 0; i < X; i++) {
        for( int j = 0; j < Y; j++) {
            M[ GETCOORDS(i,j) ] = rand() % 5;
        }
    }
    for( int i = 0; i < X; i++) {
        for( int j = 0; j < Y; j++) {
            N[ GETCOORDS(i,j) ] = rand() % 5;
        }
    }

    // M*N on host
    MatrixMultHost(M,N,P, Y);

    const std::string Phost(sprint(P));
    std::cout << Phost << std::endl;

    memset(P, 0, sizeof(float)*X*Y );

    // M*N on device
    MatrixMultDevice(M,N,P, Y);

    const std::string Pdev(sprint(P));
    std::cout << Pdev << std::endl;

    if( Phost != Pdev ){
        std::cout << "FAIL" << std::endl;
    } else{
        std::cout << "WIN" << std::endl;
    }

    // Free M, N, P
    free(M);
    free(N);
    free(P);

    return 0;
}
