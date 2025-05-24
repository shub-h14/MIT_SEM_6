//Write a program in CUDA to count the number of times a given word is repeated in a sentence.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__global__ void word_count_kernel(char* str, char* key, int str_len, int key_len, int* word_indices, int word_count, int* result) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;

    if (idx >= word_count) return;

    int si = word_indices[idx];
    int ei = (idx + 1 < word_count) ? word_indices[idx + 1] : str_len;
    
    bool is_equal = true;
    int i1 = si, i2 = 0;

    while (i1 < ei && i2 < key_len) {
        if (str[i1] != key[i2]) {
            is_equal = false;
            break;
        }
        i1++;
        i2++;
    }

    if (is_equal && i2 == key_len) {
        atomicAdd(result, 1);
    }
}

int main() {
    char str[100], key[20];
    printf("Enter string: ");
    scanf("%[^\n]s", str);
    printf("Enter key: ");
    scanf("%s", key);

    int str_len = strlen(str), key_len = strlen(key);

    int word_count = 0;
    int* word_indices = (int*)malloc((str_len / 2 + 1) * sizeof(int));  

    word_indices[word_count++] = 0;  

    for (int i = 0; i < str_len; i++) {
        if (str[i] == ' ') {
            word_indices[word_count++] = i + 1;
        }
    }

    char* d_str;
    char* d_key;
    int* d_word_indices;
    int* d_result;
    
    cudaMalloc((void**)&d_str, str_len * sizeof(char));
    cudaMalloc((void**)&d_key, key_len * sizeof(char));
    cudaMalloc((void**)&d_word_indices, word_count * sizeof(int));
    cudaMalloc((void**)&d_result, sizeof(int));
    
    cudaMemcpy(d_str, str, str_len * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_key, key, key_len * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_word_indices, word_indices, word_count * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemset(d_result, 0, sizeof(int));

    int grid_size = (word_count + 256 - 1) / 256;

    word_count_kernel<<<grid_size, 256>>>(d_str, d_key, str_len, key_len, d_word_indices, word_count, d_result);
    int result = 0;
    cudaMemcpy(&result, d_result, sizeof(int), cudaMemcpyDeviceToHost);

    printf("Input String: %s\n", str);
    printf("Key: %s\n", key);
    printf("Total occurrences of '%s': %d\n", key, result);

    cudaFree(d_str);
    cudaFree(d_key);
    cudaFree(d_word_indices);
    cudaFree(d_result);
    free(word_indices);
    return 0;
}
