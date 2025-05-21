//Write a MPI program where the master process (process 0) sends a number to each of
//the slaves and the slave processes receive the number and prints it. Use standard send.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int number;
    MPI_Status status;
   
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter an integer to send to all processes: ");
        scanf("%d", &number);

        for (int i = 1; i < size; i++) {
            printf("Master (Process 0): Sending number %d to Process %d\n", number, i);
            MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process %d: Received number %d from Process 0\n", rank, number);
    }

    MPI_Finalize();
    return 0;
}


