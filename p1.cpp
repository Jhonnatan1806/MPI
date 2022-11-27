# include <iostream>
# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# define REP 1000

int main ( int argc, char *argv[] ){
  int rank, i, size, ant, sig;
  double t1, t2;
  unsigned char msg;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  sig = (rank+1)%size;

  if(rank > 0) {
  	ant = rank - 1;
  } else {
  	ant = size - 1;	
  }
  
  printf("Soy %d, mis vecinos son %d, %d\n", rank, ant, sig);
	t1 = MPI_Wtime();

  for(i=0; i<REP; i++) {
  	if(rank == 0){
		MPI_Send(&msg, 0, MPI_BYTE, sig, i, MPI_COMM_WORLD);
		MPI_Recv(&msg, 0, MPI_BYTE, ant, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	} else {
		MPI_Recv(&msg, 0, MPI_BYTE, ant, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Send(&msg, 0, MPI_BYTE, sig, i, MPI_COMM_WORLD);
	}
  }

  t2 = MPI_Wtime();

  if(rank == 0) {
  	printf("Latencia con %d procesos %f\n", size, (t2-t1)/REP);
  }

  MPI_Finalize();
  return 0;
}