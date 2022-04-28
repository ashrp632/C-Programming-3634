#include <stdio.h>
#include <stdlib.h>
#include "fuzzykmeans.h"
#include "oracle.h"


int main(int argc, char **argv){
  int n, k;
  n = atoi(argv[1]);
  k = atoi(argv[2]);
  
  double* data = (double*)calloc(2*n,sizeof(double));
  double* clusters = (double*)calloc(2*k,sizeof(double));
  double* xdata = (double*)calloc(n,sizeof(double));
  double* ydata = (double*)calloc(n,sizeof(double));
  double* xparam = (double*)calloc(2,sizeof(double));
  double* yparam = (double*)calloc(2,sizeof(double));
  
  oracle(data,0,n);
  
  int odd = 0;
  for(int x = 0; x < 2*n; x+=2){
    xdata[odd] = data[x];
    odd++;
  }
  int even = 0;
  for(int y = 1; y <2*n; y+=2){
    ydata[even] = data[y];
    even++;
  }
  

  for(int b = 0; b < n; b++){
    if(xparam[0] < xdata[b]){
      xparam[0] = xdata[b];
    }
    if(xparam[1] > xdata[b]){
      xparam[1] = xdata[b];
    }
    if(yparam[0] < ydata[b]){
      yparam[0] = ydata[b];
    }
    if(yparam[1] > ydata[b]){
      yparam[1] = ydata[b];
    }
  }
  
  for(int c = 0; c <2*n; c++){
    printf("%f\n",data[c]);
  }

  printf("\n");
  
  srand48(n);
  for(int c = 0; c < 2*k; c+=2){
    clusters[c] = drand48()*(xparam[0]-xparam[1]+1) + xparam[1];
    clusters[c+1] = drand48()*(yparam[0]-yparam[1]+1) + yparam[1];
  }

  fuzzykmeans(data, n, clusters, k);
  
  for(int d = 0; d < 2*k; d+=2){
    printf("%f, %f\n", clusters[d], clusters[d+1]);
  }

  free(data);
  free(clusters);
  free(xdata);
  free(ydata);
  free(xparam);
  free(yparam);
}

