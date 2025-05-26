#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
__global__ void matmul(int *A,int *B,int *C,int n,int q){
    int row=threadIdx.y+blockDim.y*blockIdx.y;
    int col=threadIdx.x+blockDim.x*blockIdx.x;
    int sum=0;
    for(int i=0;i<n;i++)
    {
        sum+=A[row*n+i]*B[i*q+col];
    }
    C[row*q+col]=sum;
}
int main(){
    int m,n,p,q;
    int *d_A,*d_B,*d_C;
    printf("Enter m and n: ");
    scanf("%d %d",&m,&n);
    printf("Enter p and q: ");
    scanf("%d %d",&p,&q);
    int A[m][n],B[p][q],C[m][q];
    printf("Enter A:");
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&A[i][j]);
        }
    }
    printf("Enter B:");
    for(int i=0;i<p;i++){
        for(int j=0;j<q;j++){
            scanf("%d",&B[i][j]);
        }
    }
    cudaMalloc(&d_A,m*n*sizeof(int));
    cudaMalloc(&d_B,p*q*sizeof(int));
    cudaMalloc(&d_C,m*q*sizeof(int));
    cudaMemcpy(d_A,A[0],m*n*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(d_B,B[0],p*q*sizeof(int),cudaMemcpyHostToDevice);
    dim3 blck(2,2,1);
    dim3 grid(ceil(q/2.0),ceil(m/2.0));
    matmul<<<grid,blck>>>(d_A,d_B,d_C,n,q);
    cudaMemcpy(C[0],d_C,m*q*sizeof(int),cudaMemcpyDeviceToHost);
    printf("\nFinal Matrix:\n");
    for(int i=0;i<m;i++){
        for(int j=0;j<q;j++){
        printf("%3d ",C[i][j]);
        }
        printf("\n");
    }
}   
