//Write a program in CUDA to perform parallel Sparse Matrix - Vector multiplication 
//using compresssed sparse row (CSR) storage format. Represent the input sparse 
//matrix in CSR format in the host code. 

#include "cuda_runtime.h"
#include<stdio.h>
#include<string.h>
#include "device_launch_parameters.h"

__global__ void kernel(int* da,int* ca,int* ra,int* db,int* o){
    int k=threadIdx.x;
    int s=ra[k];
    int e=ra[k+1];
    for(int j=s;j<e;j++){
        o[k]+=da[j]*db[ca[j]];
    }
}

int main(){
    int m1,n1;
    printf("Enter m1,n1 : ");
    scanf("%d %d",&m1,&n1);

    int a[m1][n1],b[n1];
    int c=0;
    printf("Enter mat : ");
    for(int i=0;i<m1;i++){
        for(int j=0;j<n1;j++){
            scanf("%d",&a[i][j]);
            if(a[i][j]!=0)
                c++;
        }
    }
    
    printf("Enter vec : ");
    for(int i=0;i<n1;i++)
        scanf("%d",&b[i]);
    
    int data[c],col[c],row[m1+1];
    int k1=0,k2=0;
    row[m1]=c;
    for(int i=0;i<m1;i++){
        row[k2++]=k1;
        for(int j=0;j<n1;j++){
            if(a[i][j]!=0){
                data[k1]=a[i][j];
                col[k1++]=j;
            }
        }
    }

    int* da,*ca,*ra,*db,*o;
    cudaMalloc((void **)&da, c * sizeof(int));
    cudaMalloc((void **)&ca, c * sizeof(int));
    cudaMalloc((void **)&ra, (m1+1) * sizeof(int));
    cudaMalloc((void **)&db, n1 * sizeof(int));
    cudaMalloc((void **)&o, m1*sizeof(int));

    cudaMemcpy(da,data, c * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(ca,col, c * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(ra,row, (m1+1) * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(db,b, n1 * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemset(o, 0, m1 * sizeof(int));


    dim3 grid(1, 1, 1);
    dim3 blk(m1, 1, 1);

    kernel<<<grid, blk>>>(da,ca, ra, db,o);

    int oh[m1];
    cudaMemcpy(oh, o, m1*sizeof(int), cudaMemcpyDeviceToHost);

    for(int i=0;i<m1;i++)
        printf("%d\t",oh[i]);
    printf("\n");
    cudaFree(da);
    cudaFree(ca);
    cudaFree(ra);
    cudaFree(db);
    cudaFree(o);
}
