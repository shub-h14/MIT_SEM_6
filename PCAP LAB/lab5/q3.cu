// CUDA program to process a 1D array containing angles in radians
// and generate sine of the angles in the output array using sinf().

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <math.h> // for sinf()

__global__ void compute_sine(float* da, float* dc, int n) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < n) {
        dc[index] = sinf(da[index]);
    }
}

int main() {
    int n;
    printf("Length of the vector: ");
    scanf("%d", &n);

    float* a = new float[n];
    float* c = new float[n];
    float* da, * dc;

    cudaMalloc((void**)&da, n * sizeof(float));
    cudaMalloc((void**)&dc, n * sizeof(float));

    printf("Enter the angles in radians:\n");
    for (int i = 0; i < n; i++)
        scanf("%f", &a[i]);

    cudaMemcpy(da, a, n * sizeof(float), cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    dim3 grid(blocksPerGrid, 1, 1);
    dim3 blk(threadsPerBlock, 1, 1);

    compute_sine<<<grid, blk>>>(da, dc, n);
    cudaMemcpy(c, dc, n * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Sine values:\n");
    for (int i = 0; i < n; i++)
        printf("sin(%f) = %f\n", a[i], c[i]);

    cudaFree(da);
    cudaFree(dc);
    delete[] a;
    delete[] c;

    return 0;
}
