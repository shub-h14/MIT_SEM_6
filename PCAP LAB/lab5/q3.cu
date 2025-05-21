//write a program in cuda to process a 1d array containg angles
//in radians to generate sine of the angles in 
//the output array.Use approariate functions.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void add_vec(float*da,float*dc){
    int index=blockIdx.x*blockDim.x+threadIdx.x;
    dc[index]=sinf(da[index]);
}

int main(){
    int n;
    printf("Length of the vector : ");
    scanf("%d",&n);

    float a[n],c[n];
    float *da,*dc;

    cudaMalloc((void **)&da,n*sizeof(float));
    cudaMalloc((void **)&dc,n*sizeof(float));

    printf("Enter vector one : ");
    for(int i=0;i<n;i++)
        scanf("%f",&a[i]);
    
    cudaMemcpy(da,a,n*sizeof(int),cudaMemcpyHostToDevice);

    dim3 grid(n,1,1);
    dim3 blk(1,1,1);

    add_vec<<<grid,blk>>>(da,dc);
    cudaMemcpy(c,dc,n*sizeof(int),cudaMemcpyDeviceToHost);

    for(int i=0;i<n;i++)
        printf("%f\t",c[i]);
    printf("\n");
    cudaFree(da);
    cudaFree(dc);
}
