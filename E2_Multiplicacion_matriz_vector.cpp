# include <iostream>
# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define N 16

int main(int argc, char **argv) 
{
	int rank, size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	double t1, t2, t3, tp;
	int A[N][N]; 
	int vector[N], row[N/size][N], x[N];
	int sum[N/size];
	
	if(rank == 0)
	{
		srand(time(NULL));
		// generamos los valores de la matriz A
		for(int i = 0; i<N; i++)
			for(int j = 0; j<N; j++)
				A[i][j] = rand()%64 + 1;
		// generamos los valores de el vector v
		for(int i = 0; i<N; i++)
			vector[i] = rand()%4 +1;
	}

	// Broadcast p0 envia el vector v hacia p1,p2,...
	t1 = MPI_Wtime();
	MPI_Bcast(&vector,N,MPI_INT,0,MPI_COMM_WORLD);
	t1 = MPI_Wtime() - t1;

	// Scatter p0 envia k bloques de filas A hacia p1,p2,...
	// donde k = N/#p
	t2 = MPI_Wtime(); 
	MPI_Scatter(&A,(N/size)*N,MPI_INT,row,(N/size)*N,MPI_INT,0,MPI_COMM_WORLD);
	t2 = MPI_Wtime() - t2;

	tp = MPI_Wtime(); 
	// realizamos las sumas locales en p1,p2,...
	for(int i = 0; i<(N/size); i++)
		for(int j = 0; j<N; j++)
			sum[i] += row[i][j]*vector[j];
	tp = MPI_Wtime() - tp; 

	// Gather p0 almacena las sumas locales en el array X
	t3 = MPI_Wtime(); 
	MPI_Gather(&sum,(N/size),MPI_INT,x,1,MPI_INT,0,MPI_COMM_WORLD);
	t3 = MPI_Wtime() - t3; 

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
        printf("Tiempo en paralelo: %f\n",tp);
	}

	MPI_Finalize();
}