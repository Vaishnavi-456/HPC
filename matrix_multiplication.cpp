%%cuda
#include <stdio.h>
#include <cuda.h>

#define row1 2 /* Number of rows of first matrix */
#define col1 3 /* Number of columns of first matrix */
#define row2 3 /* Number of rows of second matrix */
#define col2 2 /* Number of columns of second matrix */

__global__ void matproduct(int *l, int *m, int *n) {
    int x = blockIdx.x;
    int y = blockIdx.y;
    int k;

    // Ensuring we stay within bounds
    if (x < col2 && y < row1) {
        n[col2 * y + x] = 0;
        for (k = 0; k < col1; k++) {
            n[col2 * y + x] += l[col1 * y + k] * m[col2 * k + x];
        }
    }
}

int main() {
    int a[row1][col1];
    int b[row2][col2];
    int c[row1][col2];
    int *d, *e, *f;
    int i, j;

    // Input matrices
    printf("\nEnter elements of first matrix of size 2x3\n");
    for (i = 0; i < row1; i++) {
        for (j = 0; j < col1; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("\nEnter elements of second matrix of size 3x2\n");
    for (i = 0; i < row2; i++) {
        for (j = 0; j < col2; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    // Memory allocation on the device
    cudaMalloc((void **)&d, row1 * col1 * sizeof(int));
    cudaMalloc((void **)&e, row2 * col2 * sizeof(int));
    cudaMalloc((void **)&f, row1 * col2 * sizeof(int));

    // Copy matrices to device memory
    cudaMemcpy(d, a, row1 * col1 * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(e, b, row2 * col2 * sizeof(int), cudaMemcpyHostToDevice);

    // Define grid dimensions
    dim3 grid(col2, row1);

    // Launch kernel
    matproduct<<<grid, 1>>>(d, e, f);

    // Check for errors after kernel launch
    cudaError_t errSync = cudaGetLastError();
    cudaError_t errAsync = cudaDeviceSynchronize();
    if (errSync != cudaSuccess) 
        printf("Sync kernel error: %s\n", cudaGetErrorString(errSync));
    if (errAsync != cudaSuccess) 
        printf("Async kernel error: %s\n", cudaGetErrorString(errAsync));

    // Copy the result matrix back to host memory
    cudaMemcpy(c, f, row1 * col2 * sizeof(int), cudaMemcpyDeviceToHost);

    // Print the result
    printf("\nProduct of two matrices:\n");
    for (i = 0; i < row1; i++) {
        for (j = 0; j < col2; j++) {
            printf("%d\t", c[i][j]);
        }
        printf("\n");
    }

    // Free device memory
    cudaFree(d);
    cudaFree(e);
    cudaFree(f);

    return 0;
}
