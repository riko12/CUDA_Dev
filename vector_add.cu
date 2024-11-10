// vector_add.cu
#include <cuda_runtime.h>
#include <stdio.h>

// CUDA Kernel for vector addition
__global__ void vectorAdd(const float* a, const float* b, float* c, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        c[idx] = a[idx] + b[idx];
    }
}

// CUDA function wrapper that can be called from C++
extern "C" bool cuda_vector_add(const float* h_a, const float* h_b, float* h_c, int n) {
    float *d_a, *d_b, *d_c;
    
    // Allocate device memory
    cudaError_t err = cudaMalloc(&d_a, n * sizeof(float));
    if (err != cudaSuccess) return false;
    err = cudaMalloc(&d_b, n * sizeof(float));
    if (err != cudaSuccess) {
        cudaFree(d_a);
        return false;
    }
    err = cudaMalloc(&d_c, n * sizeof(float));
    if (err != cudaSuccess) {
        cudaFree(d_a);
        cudaFree(d_b);
        return false;
    }

    // Copy inputs to device
    cudaMemcpy(d_a, h_a, n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, n * sizeof(float), cudaMemcpyHostToDevice);

    // Launch kernel
    int blockSize = 256;
    int numBlocks = (n + blockSize - 1) / blockSize;
    vectorAdd<<<numBlocks, blockSize>>>(d_a, d_b, d_c, n);

    // Copy result back to host
    cudaMemcpy(h_c, d_c, n * sizeof(float), cudaMemcpyDeviceToHost);

    // Cleanup
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return true;
}