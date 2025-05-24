//Write a program in CUDA to multiply two matrices for the following specifications:
//a. Each row of resultant matrix to be computed by one thread.
//b. Each column of resultant matrix to be computed by one thread.
//c. Each element of resultant matrix to be computed by one thread.

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

__global__ void multiply_matrices_row(int *a, int *b, int *c, int n, int m, int k)
{
        int row = blockIdx.x;
        for (int col = 0; col < k; col++)
        {
                int sum = 0;
                for (int i = 0; i < m; i++)
                {
                        sum += a[row * m + i] * b[i * k + col];
                }
                c[row * k + col] = sum;
        }
}

__global__ void multiply_matrices_col(int *a, int *b, int *c, int n, int m, int k)
{
        int col = blockIdx.x;
        for (int row = 0; row < n; row++)
        {
                int sum = 0;
                for (int i = 0; i < m; i++)
                {
                        sum += a[row * m + i] * b[i * k + col];
                }
                c[row * k + col] = sum;
        }
}

__global__ void multiply_matrices_elem(int *a, int *b, int *c, int n, int m, int k)
{
        int tid = blockIdx.x * blockDim.x + threadIdx.x;
        if (tid < n * k)
        {
                int row = tid / k;
                int col = tid % k;
                int sum = 0;
                for (int i = 0; i < m; i++)
                {
                        sum += a[row * m + i] * b[i * k + col];
                }
                c[row * k + col] = sum;
        }
}

int main()
{
        int *a, *b, *c;
        int *d_a, *d_b, *d_c;
        int n, m, k;

        printf("Enter dimensions of matrix A (n x m): ");
        scanf("%d%d", &n, &m);
        printf("Enter dimensions of matrix B (m x k): ");
        scanf("%d%d", &m, &k);

        int size_a = n * m * sizeof(int);
        int size_b = m * k * sizeof(int);
        int size_c = n * k * sizeof(int);
        a = (int *)malloc(size_a);
        b = (int *)malloc(size_b);
        c = (int *)malloc(size_c);
        cudaMalloc(&d_a, size_a);
        cudaMalloc(&d_b, size_b);
        cudaMalloc(&d_c, size_c);

        printf("Enter matrix A: \n");
        for (int i = 0; i < n; i++)
        {
                for (int j = 0; j < m; j++)
                {
                        scanf("%d", &a[i * m + j]);
                }
        }
        printf("Enter matrix B: \n");
        for (int i = 0; i < m; i++)
        {
                for (int j = 0; j < k; j++)
                {
                        scanf("%d", &b[i * k + j]);
                }
        }
        cudaMemcpy(d_a, a, size_a, cudaMemcpyHostToDevice);
        cudaMemcpy(d_b, b, size_b, cudaMemcpyHostToDevice);

        dim3 grid_size_row(n, 1, 1);
        dim3 block_size_row(1, 1, 1);
        dim3 grid_size_col(k, 1, 1);
        dim3 block_size_col(1, 1, 1);
        dim3 grid_size_elem((n * k + 255) / 256, 1, 1);
        dim3 block_size_elem(256, 1, 1);

        int option;
        printf("Enter option(1. Row-wise 2. Column-wise 3. Element-wise) :\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
                multiply_matrices_row<<<grid_size_row, block_size_row>>>(d_a, d_b, d_c, n, m, k);
                cudaMemcpy(c, d_c, size_c, cudaMemcpyDeviceToHost);
                printf("Matrix multiplication row-wise: \n");
                for (int i = 0; i < n; i++)
                {
                        for (int j = 0; j < k; j++)
                        {
                                printf("%d ", c[i * k + j]);
                        }
                        printf("\n");
                }
                printf("\n");
                break;
        case 2:
                multiply_matrices_col<<<grid_size_col, block_size_col>>>(d_a, d_b, d_c, n, m, k);
                cudaMemcpy(c, d_c, size_c, cudaMemcpyDeviceToHost);
                printf("Matrix multiplication column-wise: \n");
                for (int i = 0; i < n; i++)
                {
                        for (int j = 0; j < k; j++)
                        {
                                printf("%d ", c[i * k + j]);
                        }
                        printf("\n");
                }
                printf("\n");

                break;
        case 3:
                multiply_matrices_elem<<<grid_size_elem, block_size_elem>>>(d_a, d_b, d_c, n, m, k);
                cudaMemcpy(c, d_c, size_c, cudaMemcpyDeviceToHost);
                printf("Matrix multiplication element-wise: \n");
                for (int i = 0; i < n; i++)
                {
                        for (int j = 0; j < k; j++)
                        {
                                printf("%d ", c[i * k + j]);
                        }
                        printf("\n");
                }
                printf("\n");

                break;
        }
        free(a);
        free(b);
        free(c);
        cudaFree(d_a);
        cudaFree(d_b);
        cudaFree(d_c);
        return 0;
}
