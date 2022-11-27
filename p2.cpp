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
	
	int A[N*N], B[N*N], vector[N], row[N], sum[N];
	
	if(rank == 0)
	{
		// obtenemos los valores de A
		srand(time(NULL));
		for(int i = 0; i<N*N; i++)
			A[i] = rand()%64 + 1;
		// obtenemos los valores de v
		for(int i = 0; i<N; i++)
			vector[i] = rand()%4 +1;
	}

	// enviar datos del array A tomados de N en N
	MPI_Scatter(&A,N,MPI_INT,row,N,MPI_INT,0,MPI_COMM_WORLD);

	// enviar datos del vector
	MPI_Bcast(&vector,N,MPI_INT,0,MPI_COMM_WORLD);

	for(int i = 0; i<N; i++)
		sum[i] += row[i]*vector[i];

	// recibe el vector suma
	MPI_Gather(&sum,N,MPI_INT,B,N,MPI_INT,0,MPI_COMM_WORLD);

	if(rank == 0)
	{
		for(int i = 0; i<N*N; i++)
		{
			if(i%N == 0)
				printf("\n");
			printf("%d ",B[i]);
		}
		printf("\n");
	}

	MPI_Finalize();
}