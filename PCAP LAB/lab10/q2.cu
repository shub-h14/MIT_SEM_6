#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
__device__ int findgtid()
{
    int tnb,bng,ntpd;
    ntpd=blockDim.x*blockDim.y*blockDim.z;
    tnb=threadIdx.x+blockDim.x*threadIdx.y+blockDim.x*blockDim.y*threadIdx.z;
    bng=blockIdx.x+gridDim.x*blockIdx.y+gridDim.x*gridDim.y*blockIdx.z;
    return bng*ntpd+tnb;
}
__global__ void mykernel(int *A,int *B,int* C,int m)
{
    int gtid=findgtid();
    __shared__ int sA[10],sC[5];
    sA[gtid]=A[gtid];
    if(gtid<m) sC[gtid]=C[gtid];
    __syncthreads();
    int sum=0;
    int sp=gtid-m/2;
    for(int i=0;i<m;i++)
    {
        if(sp+i>=0 && sp+i<blockDim.x)sum+=sA[sp+i]*sC[i];
    }
    B[gtid]=sum;
}

int main()
{
    int *A,*B,*C;
    int n=10,m=5;
    int *d_A,*d_B,*d_C;
    size_t s=sizeof(int) * n;
    size_t m1=sizeof(int)*m;
    A=(int *)malloc(s);
    B=(int *)malloc(s);
    C=(int *)malloc(m1);
    cudaMalloc(&d_A,s);
    cudaMalloc(&d_B,s);
    cudaMalloc(&d_C,m1);
    printf("Enter Array:");
    for(int i=0;i<n;i++)scanf("%d",&A[i]);
    printf("Enter Mask:");
    for(int i=0;i<m;i++)scanf("%d",&C[i]);
    cudaMemcpy(d_A,A,s,cudaMemcpyHostToDevice);
    cudaMemcpy(d_C,C,m1,cudaMemcpyHostToDevice);
    mykernel<<<1,n>>>(d_A,d_B,d_C,m);
    cudaMemcpy(B,d_B,s,cudaMemcpyDeviceToHost);
    printf("Final vector:");
    for(int i=0;i<n;i++)printf("%d ",B[i]);
    free(A);
    free(B);
    free(C);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    return 0;
}
