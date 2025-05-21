//write a program in cuda to add two vectors of length N using 
//b)N threads 

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void add_vec(int* da, int* db, int* dc) {
    int index = threadIdx.x;
    dc[index] = da[index] + db[index];
}

int main() {
    int n;
    printf("Length of the vector (<= 1024): ");
    scanf("%d", &n);

    if (n > 1024) {
        printf("Error: Maximum threads per block is 1024. Please enter n <= 1024.\n");
        return -1;
    }

    int* a = new int[n];
    int* b = new int[n];
    int* c = new int[n];

    printf("Enter vector one: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    printf("Enter vector two: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    int* da, * db, * dc;

    cudaMalloc((void**)&da, n * sizeof(int));
    cudaMalloc((void**)&db, n * sizeof(int));
    cudaMalloc((void**)&dc, n * sizeof(int));

    cudaMemcpy(da, a, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(db, b, n * sizeof(int), cudaMemcpyHostToDevice);

    dim3 grid(1);
    dim3 blk(n);
    add_vec<<<grid, blk>>>(da, db, dc);

    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        printf("CUDA kernel launch error: %s\n", cudaGetErrorString(err));
        return -1;
    }

    cudaDeviceSynchronize();

    cudaMemcpy(c, dc, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Resultant vector: ");
    for (int i = 0; i < n; i++) {
        printf("%d\t", c[i]);
    }
    printf("\n");

    delete[] a;
    delete[] b;
    delete[] c;
    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);

    return 0;
}

