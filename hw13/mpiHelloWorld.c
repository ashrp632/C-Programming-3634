#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char **argv){

  int rank, size;
  char check[4];

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if(rank % 2 == 0) 
    strncpy(check, "even", 4);
  else
    strncpy(check, "odd", 3); 

  printf("This is rank %d, which is %s\n", rank, check);
  printf("hello world from MPI process %d of %d !\n", rank, size);

  MPI_Finalize();

  }

