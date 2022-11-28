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
	
	int A[N][N], vector[N], row[N], sum[N];
	
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
		// temporal
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
	}

	// Scatter 
	MPI_Scatter(&A,N,MPI_INT,&row,N,MPI_INT,0,MPI_COMM_WORLD);

	// Broadcast
	MPI_Bcast(&vector,N,MPI_INT,0,MPI_COMM_WORLD);

	//for(int i = 0; i<N; i++)
		//sum[i] += row[i]*vector[i];

	printf("Rank %d: ", rank);
	for(int i = 0; i<N; i++)
		printf("%d ", row[i]);
	printf("\n");

	// recibe el vector suma
	//MPI_Gather(&sum,N,MPI_INT,B,N,MPI_INT,0,MPI_COMM_WORLD);


	MPI_Finalize();
}