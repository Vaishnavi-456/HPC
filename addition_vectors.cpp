%%cuda
#include<stdio.h>
#include<cuda.h>

__global__ void arradd(int *x, int *y, int *z, int N) {
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id < N) {  // Ensure the thread index is within bounds
        z[id] = x[id] + y[id];
    }
}

int main() {
    int N = 1 << 20;  // Size of the vectors (1 million elements)
    int size = N * sizeof(int);
    
    int *a, *b, *c;  // Host arrays
    int *d, *e, *f;  // Device arrays
    int i;

    // Allocate memory for the vectors on the host (CPU)
    a = (int*)malloc(size);
    b = (int*)malloc(size);
    c = (int*)malloc(size);

    // Initialize the vectors with some values (e.g., integers from 1 to N)
    for(i = 0; i < N; i++) {
        a[i] = i + 1;  // Vector A: 1, 2, 3, ..., N
        b[i] = i + 1;  // Vector B: 1, 2, 3, ..., N
    }

    // Allocate memory on the device (GPU)
    cudaMalloc((void**)&d, size);
    cudaMalloc((void**)&e, size);
    cudaMalloc((void**)&f, size);

    // Copy data from host to device
    cudaMemcpy(d, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(e, b, size, cudaMemcpyHostToDevice);

    // Set block size and grid size
    int blockSize = 256;  // Number of threads per block
    int gridSize = (N + blockSize - 1) / blockSize;  // Calculate number of blocks

    // Launch the kernel to add vectors
    arradd<<<gridSize, blockSize>>>(d, e, f, N);

    // Copy the result from device to host
    cudaMemcpy(c, f, size, cudaMemcpyDeviceToHost);

    // Print the first 10 elements of the result (for verification)
    printf("Sum of the first 10 elements of two large vectors:\n");
    for(i = 0; i < 10; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");

    // Free allocated memory
    cudaFree(d);
    cudaFree(e);
    cudaFree(f);
    free(a);
    free(b);
    free(c);

    return 0;
}
