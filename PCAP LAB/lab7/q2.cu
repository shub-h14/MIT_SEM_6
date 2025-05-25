// Write a CUDA program that reads a string S and produces the string RS as follows:
// Input string S: PCAP               
// Output string RS: PCAPPCAPCP

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__global__ void kernel(char* sin, int* sin_len, char* sout) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;

    int si = 0;
    for (int i = 0; i < idx; i++) {
        si += (*sin_len) - i;
    }

    int chars_to_copy = (*sin_len) - idx;
    for (int i = 0; i < chars_to_copy; i++) {
        sout[si + i] = sin[i];
    }
}

int main() {
    char sin[100], sout[100];
    printf("Enter string: ");
    scanf("%s", sin);

    int sin_len = strlen(sin);
    int sout_len = 0;

    for (int i = 0; i < sin_len; i++) {
        sout_len += sin_len - i;
    }

    char* d_sin;
    int* d_sin_len;
    char* d_sout;

    cudaMalloc((void**)&d_sin, sin_len * sizeof(char));
    cudaMalloc((void**)&d_sin_len, sizeof(int));
    cudaMalloc((void**)&d_sout, (sout_len + 1) * sizeof(char));  

    cudaMemcpy(d_sin, sin, sin_len * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_sin_len, &sin_len, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemset(d_sout, 0, (sout_len + 1) * sizeof(char)); 

    kernel<<<1, sin_len>>>(d_sin, d_sin_len, d_sout);

    cudaMemcpy(sout, d_sout, (sout_len + 1) * sizeof(char), cudaMemcpyDeviceToHost);
    sout[sout_len] = '\0';  

    printf("Output string RS: %s\n", sout);

    cudaFree(d_sin);
    cudaFree(d_sin_len);
    cudaFree(d_sout);

    return 0;
}
