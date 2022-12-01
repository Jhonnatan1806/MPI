# include <iostream>
# include <mpi.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>
# include <fstream>

int main(int argc, char **argv) 
{
	int rank, size;
	int seeds[2];
	int result[size];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	
	if (rank == 0)
	{
		// generamos 2 semillas aleatorias 
		srand(time(NULL));
		seeds[0] = rand()%20 + 1;
		seeds[1] = rand()%size + 1; 
	}
	
	// broadcast enviamos data de p0 a todos
	MPI_Bcast(&seeds,2,MPI_INT,0,MPI_COMM_WORLD);
	
	// se genera la semilla por proceso
	// de la forma (a+b*rank)^2
	int seed = pow(seeds[0]+seeds[1]*rank,2);
	
	// generamos un numero aleatorio con la semilla
	srand(seed);
	int random = rand()%100 + 1;
	
	// gather recibimos data de todos a p0
	MPI_Gather(&random,1,MPI_INT,result,1,MPI_INT,0,MPI_COMM_WORLD);
	
	if ( rank == 0 )
	{
		bool equalsToPaolo = true;
		printf("Paolo penso en el numero %d\n",result[0]);
		for (int i = 1; i<size; i++)
		{
			if(result[0] != result[i])
				equalsToPaolo = false;
			printf("El amigo %d penso en el numero %d\n",i,result[i]);
		}
		// verificamos si todos los resultados son iguales
		if (equalsToPaolo)
			printf("Los amigos de Paolo pensaron en el mismo numero que el\n");
		else
			printf("Los amigos de Paolo no pensaron en el mismo numero que el\n");

		std::fstream filestr;
		filestr.open("E3_Adivina_mi_numero_MPI.txt", std::fstream::out | std::fstream::app);
		filestr<<"test1\n";
		filestr.close();
	}
	
	MPI_Finalize();

	
}