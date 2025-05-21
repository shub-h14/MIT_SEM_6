// 1. Write a MPI program to read N values in the root process. Root process sends one
// value to each process. Every process receives it and finds the factorial of that number and returns
// it to the root process. Root process gathers the factorial and finds sum of it. Use N number of processes.

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

long long factorial(int n) {
    long long fact = 1;
    for (int i = 2; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main(int argc, char *argv[]) {
    int rank, size;
    int number;
    long long local_fact, *all_facts = NULL;
    int *numbers = NULL;

    MPI_Init(&argc, &argv);                    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);       
    MPI_Comm_size(MPI_COMM_WORLD, &size);      

    if (rank == 0) {
        numbers = (int *)malloc(size * sizeof(int));
        printf("Enter %d integers:\n", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &numbers[i]);
        }
    }
    MPI_Scatter(numbers, 1, MPI_INT, &number, 1, MPI_INT, 0, MPI_COMM_WORLD);

    local_fact = factorial(number);

    if (rank == 0) {
        all_facts = (long long *)malloc(size * sizeof(long long));
    }

    MPI_Gather(&local_fact, 1, MPI_LONG_LONG, all_facts, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        long long total = 0;
        for (int i = 0; i < size; i++) {
            total += all_facts[i];
        }
        printf("Sum of all factorials = %lld\n", total);
        free(numbers);
        free(all_facts);
    }

    MPI_Finalize();
    return 0;
}

