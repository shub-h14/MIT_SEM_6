// Write a program in CUDA which performs convolution operation on a 1D input 
// array N of size 'width' using a mask array M of size 'maskWidth' 
// to produce the resultant 1D array P of the same size.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

// CUDA kernel to perform 1D convolution
__global__ void convolve_1d(float* da, float* db, float* dc, int maskWidth, int width) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    int start = i - (maskWidth / 2);
    float sum = 0.0f;

    for (int j = 0; j < maskWidth; j++) {
        int idx = start + j;
        if (idx >= 0 && idx < width) {
            sum += da[idx] * db[j];
        }
    }

    dc[i] = sum;
}

int main() {
    int n1, n2;

    printf("Length of the input array: ");
    scanf("%d", &n1);

    printf("Length of the mask array: ");
    scanf("%d", &n2);

    float a[n1], b[n2], c[n1];
    float *da, *db, *dc;

    cudaMalloc((void**)&da, n1 * sizeof(float));
    cudaMalloc((void**)&db, n2 * sizeof(float));
    cudaMalloc((void**)&dc, n1 * sizeof(float));

    printf("Enter input array (N): ");
    for (int i = 0; i < n1; i++)
        scanf("%f", &a[i]);

    printf("Enter mask array (M): ");
    for (int i = 0; i < n2; i++)
        scanf("%f", &b[i]);

    cudaMemcpy(da, a, n1 * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(db, b, n2 * sizeof(float), cudaMemcpyHostToDevice);

    dim3 grid(n1, 1, 1);  // One thread per output element
    dim3 blk(1, 1, 1);

    convolve_1d<<<grid, blk>>>(da, db, dc, n2, n1);

    cudaMemcpy(c, dc, n1 * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Resultant array (P):\n");
    for (int i = 0; i < n1; i++)
        printf("%f\t", c[i]);
    printf("\n");

    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);

    return 0;
}
