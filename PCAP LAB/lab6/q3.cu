//Write a program in CUDA to perform odd even transposition sort in parallel.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void add_vec(int*da,int s,int k){
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    int temp=i*2;
    if(k==0){
        temp++;
    }
    if(temp+1>s-1)
        return;
    if(da[temp]>da[temp+1]){
        da[temp]=da[temp]^da[temp+1];
        da[temp+1]=da[temp]^da[temp+1];
        da[temp]=da[temp+1]^da[temp];
    }
}

int main(){
    int n;
    printf("Length of the vector : ");
    scanf("%d",&n);

    int a[n];
    int *da;

    cudaMalloc((void **)&da,n*sizeof(int));

    printf("Enter vector one : ");
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    
    cudaMemcpy(da,a,n*sizeof(int),cudaMemcpyHostToDevice);

    dim3 grid(n/2,1,1);
    dim3 blk(1,1,1);
    for(int i=1;i<n+1;i++){
        add_vec<<<grid,blk>>>(da,n,i%2);
    }
    cudaMemcpy(a,da,n*sizeof(int),cudaMemcpyDeviceToHost);

    for(int i=0;i<n;i++)
        printf("%d\t",a[i]);
    printf("\n");
    cudaFree(da);
}
