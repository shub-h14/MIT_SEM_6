// 2. Write a MPI program to read an integer value M and NXM elements into an ID array in the root
// process, where N is the number of processes. Root process sends M elements to each process. Each process
// finds average of M elements it received and sends these average values to root. Root collects all
// the values and finds the total average. Use collective communication routines.

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, M;
    float *data = NULL, *sub_data = NULL;
    float local_sum = 0, local_avg = 0;
    float *averages = NULL, total_avg = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter number of elements per process (M): ");
        scanf("%d", &M);

        data = (float *)malloc(size * M * sizeof(float));
        printf("Enter %d float values:\n", size * M);
        for (int i = 0; i < size * M; i++) {
            scanf("%f", &data[i]);
        }
    }

    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);

    sub_data = (float *)malloc(M * sizeof(float));

    MPI_Scatter(data, M, MPI_FLOAT, sub_data, M, MPI_FLOAT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < M; i++) {
        local_sum += sub_data[i];
    }
    local_avg = local_sum / M;

    if (rank == 0) {
        averages = (float *)malloc(size * sizeof(float));
    }

    MPI_Gather(&local_avg, 1, MPI_FLOAT, averages, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            total_avg += averages[i];
        }
        total_avg /= size;
        printf("Total average = %.2f\n", total_avg);
        free(data);
        free(averages);
    }

    free(sub_data);
    MPI_Finalize();
    return 0;
}

