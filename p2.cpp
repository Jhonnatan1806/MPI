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
	int sum=0;
	
	if(rank == 0)
	{
		srand(time(NULL));
		// obtenemos los valores de A
		for(int i = 0; i<N; i++)
			for(int j = 0; j<N; j++)
				A[i][j] = rand()%64 + 1;
		// obtenemos los valores de v
		for(int i = 0; i<N; i++)
			vector[i] = rand()%4 +1;
	}

	// Broadcast
	MPI_Bcast(&vector,N,MPI_INT,0,MPI_COMM_WORLD);

	// Scatter 
	MPI_Scatter(&A,N,MPI_INT,&row,N,MPI_INT,0,MPI_COMM_WORLD);

	// realizamos suma en cada proceso
	printf("Rank %d: ",rank);
	for(int i = 0; i<N; i++)
	{
		sum += row[i]*vector[i];
		if (i != 0)
			printf("+");
		printf("(%d)(%d)",row[i],vector[i]);
	}
	printf(" = %d\n: ",sum);

	// Gather
	MPI_Gather(&sum,1,MPI_INT,x,1,MPI_INT,0,MPI_COMM_WORLD);

	if(rank == 0)
	{
		printf("A.v\n");
		for(int i = 0; i<N; i++)
			printf("%d ", x[i]);
		printf("\n");
	}

	MPI_Finalize();
}