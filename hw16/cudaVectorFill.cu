#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

__global__ void vectorFillKernel(int N, double *x){

  const int thread = threadIdx.x;
  const int block = blockIdx.x;
  const int dim = blockDim.x;
  const int grid = gridDim.x;

  int n = thread + block*dim; // n in range [0,grid*dim)

  while(n<N){
    x[n] = 999;
    n += grid*dim;
  }
}

// will execute on the HOST (CPU)
int main(int argc, char **argv){
    
  int G = 4; // 10 thread blocks
  int B = 64; // 20 threads per thread-block

  int N = 10000;
  double *c_x;
  double *h_x = (double*) calloc(N, sizeof(double));

  cudaMalloc(&c_x, N*sizeof(double));

  vectorFillKernel <<< G, B >>> (N, c_x);

  cudaMemcpy(h_x, c_x, N*sizeof(double), cudaMemcpyDeviceToHost);
  h_x[0]=0;  

  for(int n=0;n<N;++n){
    if(n == 0){
      h_x[0]=0;
      printf("h_x[%d] = %f\n", n, h_x[n]);
    }
    else {
      h_x[n] = h_x[n-1]+ 1;
      printf("h_x[%d] = %f\n", n, h_x[n]);
    }
  }

  cudaFree(c_x);
}
