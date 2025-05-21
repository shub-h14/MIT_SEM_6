//Implement a cuda program to add two vectors of length N 
//by keeping the number of threads per block as 256 (constant) 
//and vary the number of blocks to handle N elements.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define THREADS_PER_BLOCK 256

__global__ void add_vec(int* a, int* b, int* c, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n)
        c[idx] = a[idx] + b[idx];
}

int main() {
    int n;
    printf("Enter length of vectors: ");
    scanf("%d", &n);

    int* h_a = (int*)malloc(n * sizeof(int));
    int* h_b = (int*)malloc(n * sizeof(int));
    int* h_c = (int*)malloc(n * sizeof(int));

    printf("Enter vector one:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &h_a[i]);

    printf("Enter vector two:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &h_b[i]);

    int* d_a, * d_b, * d_c;
    cudaMalloc((void**)&d_a, n * sizeof(int));
    cudaMalloc((void**)&d_b, n * sizeof(int));
    cudaMalloc((void**)&d_c, n * sizeof(int));

    cudaMemcpy(d_a, h_a, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, n * sizeof(int), cudaMemcpyHostToDevice);

    int blocks = (n + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK;

    add_vec<<<blocks, THREADS_PER_BLOCK>>>(d_a, d_b, d_c, n);
    cudaDeviceSynchronize();

    cudaMemcpy(h_c, d_c, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Resultant vector:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", h_c[i]);
    printf("\n");

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(h_a);
    free(h_b);
    free(h_c);

    return 0;
}

