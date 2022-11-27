# include <iostream>
# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>

# define N 4

int main(int argc, char **argv) 
{
	int rank, size;
	int matrix[N][N];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	matrix[0][0] = 10;
	matrix[0][1] = 11;
	printf("Matriz %d\n",matrix[0]);
	MPI_Finalize();
}