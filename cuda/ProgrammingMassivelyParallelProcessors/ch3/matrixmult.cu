#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>

#define X 16 //will fail with 23, as sqrt(512) 22.sth and there can only be 512 threads per block
#define Y 16

#define GETCOORDS(row, col) (row) * (Y) + (col)

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

    int tx = threadIdx.x;
    int ty = threadIdx.y;

    float sum = 0.0f;
    for(int i=0; i < width; i++){
        float elemM = Md[ GETCOORDS(tx,i) ];
        float elemN = Nd[ GETCOORDS(i,ty) ];

        sum += elemM * elemN;
    }
    Pd[tx*width + ty] = sum;

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

    //2. kernel invokation 
    dim3 dimBlock(width, width);
    dim3 dimGrid(1,1);
    MatrixMulKernel<<<dimGrid, dimBlock>>>(Md, Nd, Pd, width);

    //3. copy P from device to host
    cudaMemcpy(P, Pd, size, cudaMemcpyDeviceToHost);

    //4. Free Md, Nd, Pd
    cudaFree(Md);
    cudaFree(Nd);
    cudaFree(Pd);
}


int main(){
    float *M, *N, *P;

    // allocate M, N, P
    M = (float*)malloc( sizeof(float)*X*Y );
    N = (float*)malloc( sizeof(float)*X*Y );
    P = (float*)malloc( sizeof(float)*X*Y );

    for( int i = 0; i < X; i++) {
        for( int j = 0; j < Y; j++) {
            M[ GETCOORDS(i,j) ] = i+j;
        }
    }
    for( int i = 0; i < X; i++) {
        for( int j = 0; j < Y; j++) {
            N[ GETCOORDS(i,j) ] = i*j;
        }
    }

    // M*N on host
    MatrixMultHost(M,N,P, Y);

    const std::string Phost(sprint(P));
    //std::cout << Phost << std::endl;

    memset(P, 0, sizeof(float)*X*Y );

    // M*N on device
    MatrixMultDevice(M,N,P, Y);

    const std::string Pdev(sprint(P));
    //std::cout << Pdev << std::endl;

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
