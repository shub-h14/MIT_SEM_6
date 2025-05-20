#include <stdio.h>
#include <mpi.h>
#include <string.h>

char toggle(char c) {
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    else if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

int main(int argc, char *argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc < 2) {
        if (rank == 0)
            printf("Usage: %s <string>\n", argv[0]);
        MPI_Finalize();
        return 0;
    }

    char *input = argv[1];
    int len = strlen(input);

    if (rank < len) {
        char original = input[rank];
        char toggled = toggle(original);
        printf("Rank %d: '%c' -> '%c'\n", rank, original, toggled);
    }

    MPI_Finalize();
    return 0;
}

