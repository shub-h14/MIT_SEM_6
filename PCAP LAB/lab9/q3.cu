#include "cuda_runtime.h"
#include<stdio.h>
#include<string.h>
#include "device_launch_parameters.h"

__global__ void kernel(int* da,int n1){
    int k=threadIdx.x;
    if(k==0||k==blockDim.x-1)
        return;
    printf("%d\n",(int)powf(10,0));
    for(int j=1;j<n1-1;j++){
        int num=da[k*n1+j];
        int out=0,pow=0,place=1;
        while(num){
            int tt=1;
            if(num%2)
                tt=0;
            out=tt*place+out;
            num/=2;
            place*=10;
            printf("%d - %d - %d\n",k,j,out);
        }
        da[k*n1+j]=out;
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
