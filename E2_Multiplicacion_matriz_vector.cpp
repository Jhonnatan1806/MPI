# include <iostream>
# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main(int argc, char **argv) 
{
	int rank, size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	const int N = size;
	
	int A[N][N], vector[N], row[N], x[N];
	int sum=0;
	
	if(rank == 0)
	{
		srand(time(NULL));
		// generamos los valores de A
		for(int i = 0; i<N; i++)
			for(int j = 0; j<N; j++)
				A[i][j] = rand()%64 + 1;
		// generamos los valores de v
		for(int i = 0; i<N; i++)
			vector[i] = rand()%4 +1;
	}

	// Broadcast p0 envia el vector v a p1,p2,...
	MPI_Bcast(&vector,N,MPI_INT,0,MPI_COMM_WORLD);

	// Scatter p0 envia las filas de A a p1,p2,... 
	MPI_Scatter(&A,N,MPI_INT,row,N,MPI_INT,0,MPI_COMM_WORLD);

	// realizamos las sumas locales en p1,p2,...
	for(int i = 0; i<N; i++)
		sum += row[i]*vector[i];

	// Gather p0 almacena las sumas locales en el array X
	MPI_Gather(&sum,1,MPI_INT,x,1,MPI_INT,0,MPI_COMM_WORLD);

	// Imprimir el vector x[] en p0
	if(rank == 0)
	{
		printf("x = [ ");
		for (int i : x)
        	printf("%d ", i);
        printf("]\n");
	}

	MPI_Finalize();
}