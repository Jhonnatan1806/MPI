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
	
	int A[N*N], vector[N], row[N];
	
	if(rank == 0)
	{
		// obtenemos los valores de A
		srand(time(NULL));
		for( int i = 0; i<N*N; i++)
			A[i] = i+1;//rand()%64 + 1;
		// obtenemos los valores de v
		for( int i = 0; i<N; i++)
			vector[i] = 2;//rand()%64 +1;
	}

	// enviar datos del array A tomados de N en N
	MPI_Scatter(&A,N,MPI_INT,row,N,MPI_INT,0,MPI_COMM_WORLD);

	// enviar datos del vector
	MPI_Bcast(&vector,N,MPI_INT,0,MPI_COMM_WORLD);

	//imprimo matrices en cada 
	for( int i = 0; i<N; i++)
		printf("%d ",row[i]);
	printf("\n");

	if(rank == 0)
	{
		for( int i = 0; i<N; i++)
			printf("%d ",row[i]*vector[i]);
		printf("\n");
	}

	MPI_Finalize();
}