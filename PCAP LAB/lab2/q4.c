#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char *argv[]){
	int rank, size;
    int value;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
    	printf("Running root process %d and sending to %d processes.\n",rank, size-1);
        printf("Enter an integer value: ");
        scanf("%d", &value);
        
        MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        value += 1;
        
        if (rank < size - 1) {
            MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }
    }

    if (rank == size - 1) {
        MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else if (rank == 0) {
        MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Final value received by root process: %d\n", value);
    }

    MPI_Finalize();
    return 0;
}
