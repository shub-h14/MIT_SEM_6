// 3. Write a program in MPI to stimulate simple calculator. perform each
// operation using different process in parallel.

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int a, b, x, rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 3) {
        if (rank == 0) {
            fprintf(stderr, "Usage: %s <a> <b>\n", argv[0]);
        }
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    // Convert input arguments to integers
    a = atoi(argv[1]);
    b = atoi(argv[2]);

    switch(rank){
        case 0:
            x = a + b;
            printf("Rank %d gives a + b = %d\n", rank, x);
            break;
        case 1:
            x = a - b;
            printf("Rank %d gives a - b = %d\n", rank, x);
            break;
        case 2:
            x = a * b;
            printf("Rank %d gives a * b = %d\n", rank, x);
            break;
        case 3:
            if (b != 0) {
                x = a / b;
                printf("Rank %d gives a / b = %d\n", rank, x);
            } else {
                printf("Rank %d: Division by zero error\n", rank);
            }
            break;
        case 4:
            if (b != 0) {
                x = a % b;
                printf("Rank %d gives a %% b = %d\n", rank, x);
            } else {
                printf("Rank %d: Modulo by zero error\n", rank);
            }
            break;
        default:
            printf("Invalid rank number %d\n", rank);
            break;
    }

    MPI_Finalize();
    return 0;
}

