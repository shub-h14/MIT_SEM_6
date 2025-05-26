#include "cuda_runtime.h"
#include<stdio.h>
#include<string.h>
#include "device_launch_parameters.h"

__global__ void kernel(int* da,int n1){
    int k=threadIdx.x,temp;
    for(int j=0;j<n1;j++){
        temp=da[k*n1+j];
        for(int i=0;i<k;i++)
            da[k*n1+j]*=temp;
    }
}

int main(){
    int m1,n1;
    printf("Enter m1,n1 : ");
    scanf("%d %d",&m1,&n1);

    int a[m1][n1];
    printf("Enter mat : ");
    for(int i=0;i<m1;i++)
        for(int j=0;j<n1;j++)
            scanf("%d",&a[i][j]);

    int* da;
    cudaMalloc((void **)&da, (m1*n1) * sizeof(int));
    cudaMemcpy(da,a, m1*n1 * sizeof(int), cudaMemcpyHostToDevice);

    dim3 grid(1, 1, 1);
    dim3 blk(m1, 1, 1);

    kernel<<<grid, blk>>>(da,n1);

    cudaMemcpy(a, da, m1*n1*sizeof(int), cudaMemcpyDeviceToHost);

    for(int i=0;i<m1;i++){
        for(int j=0;j<n1;j++)
            printf("%d\t",a[i][j]);
        printf("\n");
    }
    cudaFree(da);
}
