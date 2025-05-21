//Write a MPI program to read N elements of the array in the root process (process 0)
//where N is equal to the total number of processes. The root process sends one value to
//each of the slaves. Let even ranked process finds square of the received element and
//odd ranked process finds cube of received element. Use Buffered send.

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int *arr = NULL;
    int value;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) {
            printf("This program needs at least 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        arr = (int *)malloc(size * sizeof(int));
        printf("Enter %d integers:\n", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }

        int bufsize = size * (MPI_BSEND_OVERHEAD + sizeof(int));
        void *buffer = malloc(bufsize);
        MPI_Buffer_attach(buffer, bufsize);

        for (int i = 1; i < size; i++) {
            MPI_Bsend(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        } 
        free(arr);
        MPI_Buffer_detach(&buffer, &bufsize);
        free(buffer);
    } else {
      
        MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        if (rank % 2 == 0) {
            printf("Process %d (even): square of %d = %d\n", rank, value, value * value);
        } else {
            printf("Process %d (odd): cube of %d = %d\n", rank, value, value * value * value);
        }
    }

    MPI_Finalize();
    return 0;
}

