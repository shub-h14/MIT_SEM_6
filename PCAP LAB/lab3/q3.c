#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <ctype.h>
#include <mpi.h>

int is_vowel(char ch) {
    ch = tolower(ch);
    return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
}

int main(int argc, char *argv[]) {
    int rank, size, str_len, chunk_size;
    char *input_str = NULL;
    char *sub_str = NULL;
    int local_count = 0, *all_counts = NULL, total = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        char temp[100];
        printf("Enter a string (length divisible by %d): ", size);
        scanf("%s", temp);

        str_len = strlen(temp);
        if (str_len % size != 0) {
            printf("Error: String length must be divisible by number of processes.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        chunk_size = str_len / size;
        input_str = temp;
    }

    MPI_Bcast(&chunk_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    sub_str = (char *)malloc((chunk_size + 1) * sizeof(char));

    MPI_Scatter(input_str, chunk_size, MPI_CHAR, sub_str, chunk_size, MPI_CHAR, 0, MPI_COMM_WORLD);
    sub_str[chunk_size] = '\0'; 

    for (int i = 0; i < chunk_size; i++) {
        if (!is_vowel(sub_str[i])) {
            local_count++;
        }
    }

    if (rank == 0) {
        all_counts = (int *)malloc(size * sizeof(int));
    }

    MPI_Gather(&local_count, 1, MPI_INT, all_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            printf("Process %d found %d non-vowels\n", i, all_counts[i]);
            total += all_counts[i];
        }
        printf("Total non-vowels: %d\n", total);
        free(all_counts);
    }

    free(sub_str);
    MPI_Finalize();
    return 0;
}

