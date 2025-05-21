//Implement a cuda program to add two vectors of length N 
//by keeping the number of threads per block as 256 (constant) 
//and vary the number of blocks to handle N elements.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void add_vec(int*da,int*db,int*dc){
    int index=blockIdx.x*blockDim.x+threadIdx.x;
    dc[index]=da[index]+db[index];
}

int main(){
    int n;
    printf("Length of the vector : ");
    scanf("%d",&n);

    int gridn=ceil(n/256);
    int a[n],b[n],c[n];
    int *da,*db,*dc;

    cudaMalloc((void **)&da,n*sizeof(int));
    cudaMalloc((void **)&db,n*sizeof(int));
    cudaMalloc((void **)&dc,n*sizeof(int));

    printf("Enter vector one : ");
    for(int i=0;i<n;i++)
        a[i]=i;

    printf("Enter vector two : ");
    for(int i=0;i<n;i++)
        b[i]=i;
    
    cudaMemcpy(da,a,n*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(db,b,n*sizeof(int),cudaMemcpyHostToDevice);

    dim3 grid(gridn,1,1);
    dim3 blk(256,1,1);

    add_vec<<<grid,blk>>>(da,db,dc);
    cudaMemcpy(c,dc,n*sizeof(int),cudaMemcpyDeviceToHost);

    for(int i=0;i<n;i++)
        printf("%d\n",c[i]);
    printf("\n");
    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);
}

