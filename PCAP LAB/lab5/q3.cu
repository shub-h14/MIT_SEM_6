//write a program in cuda to process a 1d array containg angles
//in radians to generate sine of the angles in 
//the output array.Use approariate functions.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define THREADS_PER_BLOCK 256
__global__ void compute_sine(float* angles, float* output, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n)
        output[idx] = sinf(angles[idx]);  // Use sinf for float
}
int main() {
    int n;
    printf("Enter number of angles: ");
    scanf("%d", &n);

    float* h_angles = (float*)malloc(n * sizeof(float));
    float* h_output = (float*)malloc(n * sizeof(float));

    printf("Enter %d angles in radians:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%f", &h_angles[i]);

    float *d_angles, *d_output;
    cudaMalloc((void**)&d_angles, n * sizeof(float));
    cudaMalloc((void**)&d_output, n * sizeof(float));

    cudaMemcpy(d_angles, h_angles, n * sizeof(float), cudaMemcpyHostToDevice);

    int blocks = (n + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK;
    compute_sine<<<blocks, THREADS_PER_BLOCK>>>(d_angles, d_output, n);
    cudaDeviceSynchronize();

    cudaMemcpy(h_output, d_output, n * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Sine values:\n");
    for (int i = 0; i < n; i++)
        printf("sin(%.4f) = %.4f\n", h_angles[i], h_output[i]);

    cudaFree(d_angles);
    cudaFree(d_output);
    free(h_angles);
    free(h_output);

    return 0;
}

