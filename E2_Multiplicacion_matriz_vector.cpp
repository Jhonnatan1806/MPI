# include <iostream>
# include <mpi.h>
# include <stdio.h>

# define REP 1000

int main(int argc, char **argv) 
{
	int rank, size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	const int N = size;

	double t1, t2, t3;
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
	t1 = MPI_Wtime();
	MPI_Bcast(&vector,N,MPI_INT,0,MPI_COMM_WORLD);
	t1 -= MPI_Wtime();

	// Scatter p0 envia las filas de A a p1,p2,...
	t2 = MPI_Wtime(); 
	MPI_Scatter(&A,N,MPI_INT,row,N,MPI_INT,0,MPI_COMM_WORLD);
	t2 -= MPI_Wtime();

	// realizamos las sumas locales en p1,p2,...
	for(int i = 0; i<N; i++)
		sum += row[i]*vector[i];

	// Gather p0 almacena las sumas locales en el array X
	t3 = MPI_Wtime(); 
	MPI_Gather(&sum,1,MPI_INT,x,1,MPI_INT,0,MPI_COMM_WORLD);
	t3 -= MPI_Wtime(); 

	// Imprimir el vector x[] en p0
	if(rank == 0)
	{
		printf("x = [ ");
		for (int i = 0; i<N; i++)
        	printf("%d ", x[i]);
        printf("]\n");
        printf("Tiempo Comm Bcast: %f\n",t1);
        printf("Tiempo Comm Scatter: %f\n",t2);
        printf("Tiempo Comm Gather: %f\n",t3);
	}

	MPI_Finalize();
}