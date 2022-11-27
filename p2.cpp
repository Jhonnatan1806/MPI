# include <iostream>
# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# define N 4

int main(int argc, char **argv) 
{
	int rank, size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int A[N*N];
	int vector[N],row[N];
	if(rank == 0)
	{
		// obtenemos los valores de A
		srand(time(NULL));
		for( int i = 0; i<N*N; i++)
			A[i] = i+1;//rand()%64 + 1;
		// obtenemos los valores de v
		for( int i = 0; i<N; i++)
			vector[i] = rand()%64 +1;
	}

	// enviar filas de A
	MPI_Scatter(&A,N,MPI_INT,row,0,MPI_INT,0,MPI_COMM_WORLD);
	//imprimo matrices en cada 
	for( int i = 0; i<N*N; i++)
		printf("%d ",row[i]);
	printf("\n");
	MPI_Finalize();
}