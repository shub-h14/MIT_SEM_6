#include <stdio.h>
#include <mpi.h>

#define SIZE 3

int main(int argc, char *argv[]) {
    int rank, size;
    int matrix[SIZE][SIZE];
    int row[SIZE];
    int search_element;
    int local_count = 0, total_count = 0;

    MPI_Init(&argc, &argv);               
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    if (size != 3) {
        if (rank == 0) {
            printf("This program requires exactly 3 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        printf("Enter a 3x3 matrix:\n");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }

        printf("Enter the element to search: ");
        scanf("%d", &search_element);
    }

    MPI_Bcast(&search_element, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(matrix, SIZE, MPI_INT, row, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < SIZE; i++) {
        if (row[i] == search_element) {
            local_count++;
        }
    }

    MPI_Reduce(&local_count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total occurrences of %d = %d\n", search_element, total_count);
    }

    MPI_Finalize(); 
    return 0;
}

