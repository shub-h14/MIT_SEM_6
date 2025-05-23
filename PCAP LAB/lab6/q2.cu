//Write a program in CUDA to perform selection sort in parallel.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void add_vec(int*da,int*dc,int s){
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    int k=0;
    for(int j=0;j<s;j++){
        if((da[j]<da[i])||(da[j]==da[i]&&j>i))
            k++;
    }
    dc[k]=da[i];
}

int main(){
    int n;
    printf("Length of the vector : ");
    scanf("%d",&n);

    int a[n],c[n];
    int *da,*dc;

    cudaMalloc((void **)&da,n*sizeof(int));
    cudaMalloc((void **)&dc,n*sizeof(int));

    printf("Enter vector one : ");
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    
    cudaMemcpy(da,a,n*sizeof(int),cudaMemcpyHostToDevice);

    dim3 grid(n,1,1);
    dim3 blk(1,1,1);

    add_vec<<<grid,blk>>>(da,dc,n);
    cudaMemcpy(c,dc,n*sizeof(int),cudaMemcpyDeviceToHost);

    for(int i=0;i<n;i++)
        printf("%d\t",c[i]);
    printf("\n");
    cudaFree(da);
    cudaFree(dc);
}
