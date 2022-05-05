#include <stdlib.h>
#include <stdio.h>
#include "fuzzykmeans.h"
#include "oracle.h"
#include <mpi.h>

int main(int carg,char** varg){

  MPI_Init(&carg, &varg);

  if(carg != 4){
    printf("Please provide two arguments: n and k\n");
    return 1;
  }
  int size, rank;
  int n = atoi(varg[1]);
  int k = atoi(varg[2]);
  int r = atoi(varg[3]);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if(n<=0 || k<=0){
    printf("n and k really need to be positive\n");
    return 1;
  }
  double* centers = malloc(2*k*sizeof(double));

  double tic = MPI_Wtime();

  int approx = n/size;
  int approx2 = (rank*n)/size;
  double* rankData = malloc(2*approx*sizeof(double));

  oracle(rankData, approx2, approx);

  double xglobalMin;
  double yglobalMin;
  double yglobalMax;
  double xglobalMax;

  double xlo = rankData[0];
  double xhi = rankData[0];
  double ylo = rankData[1];
  double yhi = rankData[1];

  int i;
  // Find the rectangle that bounds the data
  for(i=0;i<n/size;++i){
    if(rankData[2*i] < xlo)
      xlo = rankData[2*i];
    if(rankData[2*i] > xhi)
      xhi = rankData[2*i];
    if(rankData[2*i+1] < ylo)
      ylo = rankData[2*i+1];
    if(rankData[2*i+1] > yhi)
      yhi = rankData[2*i+1];
  }

  MPI_Allreduce(&xlo, &xglobalMin, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);
  MPI_Allreduce(&ylo, &yglobalMin, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);
  MPI_Allreduce(&xhi, &xglobalMax, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
  MPI_Allreduce(&yhi, &yglobalMax, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);


  // Select random points in the rectangle for the initial centers
  double dx = &xglobalMax-&xglobalMin;
  double dy = &yglobalMax-&yglobalMin;
  drand48();
  for(i=0;i<k;++i){
    centers[2*i  ] = drand48()*dx + xglobalMin;
    centers[2*i+1] = drand48()*dy + yglobalMin;
  }

  fuzzykmeans(rankData,n/size,centers,k);

  MPI_Status status;
  if(r == 0){
    if(rank == 0){
      double toc = MPI_Wtime();
      printf("runtime = %f\n",toc-tic);
    }
  }
  int one = 1;
  if(r==1){
    if(rank == 0){
      printf("Print rank = %d\n", rank);
      printf("Print xmin %f\n,", xglobalMin);
      printf("data = [%lf , %lf\n",rankData[0],rankData[1]);
      for(i=1;i<approx;++i)
	printf("        %lf , %lf\n",rankData[2*i],rankData[2*i+1]);
      printf("];\ncenters = [%lf , %lf\n",centers[0],centers[1]);
      for(i=1;i<k;++i)
	printf("           %lf , %lf\n",centers[2*i],centers[2*i+1]);
      printf("];\n");
      MPI_Send(&one, 1, MPI_INT, rank+1 ,1 , MPI_COMM_WORLD); 
    }
    else if(rank == size){
      MPI_Recv(&one, 1, MPI_INT, size - 1 ,1 , MPI_COMM_WORLD, &status); 
      printf("print if max\n");
      printf("data = [%lf , %lf\n",rankData[0],rankData[1]);
      for(i=1;i<approx;++i)
	printf("        %lf , %lf\n",rankData[2*i],rankData[2*i+1]);
    }
    else {
      MPI_Recv(&one, 1, MPI_INT, rank-1 ,1 , MPI_COMM_WORLD, &status); 
      printf("Print rank = %d\n", rank);
      printf("data = [%lf , %lf\n",rankData[0],rankData[1]);
      for(i=1;i<approx;++i)
	printf("        %lf , %lf\n",rankData[2*i],rankData[2*i+1]);
      MPI_Send(&one, 1, MPI_INT, rank+1 ,1 , MPI_COMM_WORLD); 
    }
  }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
  // Free data
  free(rankData);
  free(centers);
  MPI_Finalize();
    
  return 0;
}
