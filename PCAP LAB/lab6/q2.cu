//Write a program in CUDA to perform selection sort in parallel.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void selection_sort_parallel(int* da, int* dc, int size) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int position = 0;

    // Count how many elements are smaller than da[i]
    // or equal with a smaller index to maintain order for duplicates
    for (int j = 0; j < size; j++) {
        if ((da[j] < da[i]) || (da[j] == da[i] && j < i)) {
            position++;
        }
    }

    // Place element at its correct sorted position
    dc[position] = da[i];
}

int main() {
    int n;
    printf("Length of the vector : ");
    scanf("%d", &n);

    int a[n], c[n];
    int *da, *dc;

    cudaMalloc((void**)&da, n * sizeof(int));
    cudaMalloc((void**)&dc, n * sizeof(int));

    printf("Enter vector elements : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    cudaMemcpy(da, a, n * sizeof(int), cudaMemcpyHostToDevice);

    dim3 grid(n, 1, 1);
    dim3 blk(1, 1, 1);

    selection_sort_parallel<<<grid, blk>>>(da, dc, n);
    cudaMemcpy(c, dc, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sorted vector : ");
    for (int i = 0; i < n; i++)
        printf("%d\t", c[i]);
    printf("\n");

    cudaFree(da);
    cudaFree(dc);

    return 0;
}
