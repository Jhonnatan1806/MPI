# include <iostream>
# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# define N 4

int main(int argc, char **argv) 
{
	int rank, size;
	int matrix[N*N];
	int vector[N];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank == 0)
	{
		// obtenemos los valores de A
		srand(time(NULL));
		for( int i = 0; i<N*N; i++)
			matrix[i] = i;//rand()%64 + 1;
		// obtenemos los valores de v
		for( int i = 0; i<N; i++)
			vector[i] = rand()%64 +1;
		// enviar filas 
	}
	for( int i = 0; i<N*N; i++)
		printf("%d ",matrix[i]);
	printf("\n");
	MPI_Finalize();
}