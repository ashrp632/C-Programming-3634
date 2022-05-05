#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include "fuzzykmeans.h"

double dist2(double* v0, double* v1){
  double dx = v0[0]-v1[0];
  double dy = v0[1]-v1[1];
  return dx*dx + dy*dy;
}

double weight(double* d2,int j,int k){
  double w = 0;
  int el;
  for(el=0;el<k;++el){
    w += d2[j] / d2[el];
  }
  return 1/w;
}

void fuzzykmeans(double* data, int n, double* centers, int k){
  double* new_centers = (double*)malloc(2*k*sizeof(double));
  double* cluster_weights = (double*)malloc(k*sizeof(double));
  double* new_centers2 = (double*)malloc(2*k*sizeof(double));                                                                                                                                          
  double* cluster_weights2 = (double*)malloc(k*sizeof(double));

  // Squared distances
  double* d2 = (double*)malloc(k*sizeof(double));

  // Temp convenience variables
  double w,w2;

  int i,j;

  double tol = 1e-3;
  double d;
  // Make delta big enough to get in the loop the first time
  double delta = tol + 1;
  while(delta > tol){
    // The new centers and weights need to start at zero every iteration
    // in order to accumulate correctly
    for(j=0;j<k;++j){
      cluster_weights[j] = 0;
      new_centers[j] = 0;
      new_centers[j+k] = 0;
    }
    for(i=0;i<n;++i){
      // Get all distances from centers to data point i
      for(j=0;j<k;++j){
	d2[j] = dist2(data+2*i,centers+2*j);
      }
      // Add the contribution of data point i to
      // every cluster weight and center location
      for(j=0;j<k;++j){
	w = weight(d2,j,k);
	w2 = w*w;
	cluster_weights[j] += w2;
	new_centers[2*j  ] += w2*data[2*i  ];
	new_centers[2*j+1] += w2*data[2*i+1];
      }
    }

    MPI_Allreduce(new_centers, new_centers2, 2*k, MPI_DOUBLE, MPI_SUM,MPI_COMM_WORLD);                                                                                                               
    MPI_Allreduce(cluster_weights, cluster_weights2, k, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);     

    // Normalize new cluster centers by sum of weights
    for(j=0;j<2*k;++j){
      new_centers2[j] /= cluster_weights2[ j/2 ];
    }
    // Find largest coordinate change
    delta = 0;
    for(j=0;j<2*k;++j){
      d = fabs(new_centers2[j] - centers[j]);
      if(d > delta)
	delta = d;
      centers[j] = new_centers2[j];
    }
  }

  free(new_centers);
  free(cluster_weights);
  free(d2);
}

