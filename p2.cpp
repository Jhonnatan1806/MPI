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
	
	int A[N][N], vector[N], row[N], x[N];
	int sum;
	
	if(rank == 0)
	{
		// obtenemos los valores de A
		srand(time(NULL));
		for(int i = 0; i<N; i++)
			for(int j = 0; j<N; j++)
				A[i][j] = i+j;//rand()%64 + 1;
		// obtenemos los valores de v
		for(int i = 0; i<N; i++)
			vector[i] = rand()%4 +1;
	}

	// Scatter 
	MPI_Scatter(&A,N,MPI_INT,&row,N,MPI_INT,0,MPI_COMM_WORLD);

	// Broadcast
	MPI_Bcast(&vector,N,MPI_INT,0,MPI_COMM_WORLD);

	// realizamos suma en cada proceso
	for(int i = 0; i<N; i++)
		sum += row[i]*vector[i];

	// Gather
	MPI_Gather(&sum,1,MPI_INT,x,N,MPI_INT,0,MPI_COMM_WORLD);

	if(rank == 0)
	{
		printf("Matriz A\n");
		for(int i = 0; i<N; i++)
			{
			for(int j = 0; j<N; j++)
				printf("%d ", A[i][j]);
			printf("\n");
			}
		printf("Vector\n");
		for(int i = 0; i<N; i++)
			printf("%d ", vector[i]);
		printf("\n");
		printf("AxVector\n");
		for(int i = 0; i<N; i++)
			printf("%d ", x[i]);
		printf("\n");
	}

	MPI_Finalize();
}