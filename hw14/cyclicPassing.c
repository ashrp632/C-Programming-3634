#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv){

  int rank, size, *inv, *outv, i;

  inv = (int*) malloc(10*sizeof(int));
  outv = (int*) malloc(10*sizeof(int));
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  for (i = 0; i<10; i++){
    if(i<5){
      outv[i]= rank;
    }
    else{
      outv[i] = rank+10;
    }
  }
  MPI_Status status;
  if(rank ==0){
    MPI_Send(outv, 5, MPI_INT, size-1 ,1 , MPI_COMM_WORLD);     
    MPI_Send(outv+5, 5, MPI_INT, rank+1 ,1 , MPI_COMM_WORLD);
    MPI_Recv(inv, 5, MPI_INT, size-1 ,1 , MPI_COMM_WORLD, &status);
    MPI_Recv(inv+5, 5, MPI_INT, rank+1 ,1 , MPI_COMM_WORLD, &status);
   
    }
  if(rank == size-1) {
    MPI_Send(outv, 5, MPI_INT, rank-1 ,1 , MPI_COMM_WORLD);
    MPI_Send(outv+5, 5, MPI_INT, 0 , 1 , MPI_COMM_WORLD);
    MPI_Recv(inv, 5, MPI_INT, rank-1 ,1, MPI_COMM_WORLD, &status);
    MPI_Recv(inv+5, 5, MPI_INT, 0 ,1, MPI_COMM_WORLD, &status);     
    
  }
  else {
    MPI_Send(outv, 5, MPI_INT, rank-1 ,1 , MPI_COMM_WORLD);
    MPI_Send(outv+5, 5, MPI_INT, rank+1 ,1 , MPI_COMM_WORLD);
    MPI_Recv(inv, 5, MPI_INT, rank-1 ,1, MPI_COMM_WORLD, &status);
    MPI_Recv(inv+5, 5, MPI_INT, rank+1 ,1, MPI_COMM_WORLD, &status);
    }
  usleep(5e4*rank);
  printf("Rank %d outv:[", rank);
  for(int v = 0; v<10; v++){
    printf("%d ", outv[v]);
  }
  printf("]");
  printf("\n");
  printf("Rank %d inv:[", rank);
    for(int c = 0; c<10; c++){
    printf("%d ",inv[c]);
  }
  printf("]");
  printf("\n");
  free(outv);
  free(inv);

  MPI_Finalize();

}
