//Write a program in cuda which performs convolution operation on one-dimensional input 
//array N of size width using a mask array M of size_width to produce the resultant 
//one-dimensional array P of size width.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void kernel(float*da,float*db,float*dc,int mw,int w){
    int i=blockIdx.x*blockDim.x+threadIdx.x;

    int s=i-(mw)/2;
    float pv=0;
    for(int j=0;j<w;j++){
        if(s+j>=0&&s+j<w){
            pv+=da[s+j]*db[j];
        }
    }
    dc[i]=pv;
}

int main(){
    int n1,n2;

    printf("Length of the vector : ");
    scanf("%d",&n1);

    printf("Enter the length of mask : ");
    scanf("%d",&n2);


    float a[n1],b[n2],c[n1];
    float *da,*db,*dc;

    cudaMalloc((void **)&da,n1*sizeof(float));
    cudaMalloc((void **)&db,n2*sizeof(float));
    cudaMalloc((void **)&dc,n1*sizeof(float));

    printf("Enter vector one : ");
    for(int i=0;i<n1;i++)
        scanf("%f",&a[i]);

    printf("Enter vector two (aka mask) : ");
    for(int i=0;i<n2;i++)
        scanf("%f",&b[i]);
    
    cudaMemcpy(da,a,n1*sizeof(float),cudaMemcpyHostToDevice);
    cudaMemcpy(db,b,n2*sizeof(float),cudaMemcpyHostToDevice);

    dim3 grid(n1,1,1);
    dim3 blk(1,1,1);

    kernel<<<grid,blk>>>(da,db,dc,n2,n1);
    cudaMemcpy(c,dc,n1*sizeof(float),cudaMemcpyDeviceToHost);

    for(int i=0;i<n1;i++)
        printf("%f\t",c[i]);
    printf("\n");
    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);
}
