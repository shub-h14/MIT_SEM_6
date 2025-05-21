// Write a MPI program using synchronous send. The sender process sends a word to the
//receiver. The second process receives the word, toggles each letter of the word and sends
//it back to the first process. Both processes use synchronous send operations.

#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

void toggle_case(char *str) {
    for (int i = 0; str[i]; i++) {
        if (islower(str[i]))
            str[i] = toupper(str[i]);
        else if (isupper(str[i]))
            str[i] = tolower(str[i]);
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    char word[MAX_LEN];

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
        strcpy(word, "HeLLoMPI");

        printf("Process 0 sending word: %s\n", word);
        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD); 

        MPI_Recv(word, MAX_LEN, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received toggled word: %s\n", word);  
    } 
    else if (rank == 1) {
        MPI_Recv(word, MAX_LEN, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received word: %s\n", word);

        toggle_case(word);

        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

