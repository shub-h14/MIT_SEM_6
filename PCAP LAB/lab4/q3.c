#include <stdio.h>
#include <mpi.h>

#define SIZE 4

int main(int argc, char *argv[]) {
    int rank, size;
    int input_matrix[SIZE][SIZE];
    int local_row[SIZE];
    int output_row[SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    if (size != SIZE) {
        if (rank == 0)
            printf("This program requires exactly 4 processes.\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        printf("Enter a 4x4 matrix:\n");
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                scanf("%d", &input_matrix[i][j]);
    }

    MPI_Scatter(input_matrix, SIZE, MPI_INT, local_row, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scan(local_row, output_row, SIZE, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    int final_output[SIZE][SIZE];
    MPI_Gather(output_row, SIZE, MPI_INT, final_output, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Output matrix:\n");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", final_output[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}

