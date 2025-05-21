// Write a MPI program to read a word of length N. Using N processes including
// the root get output word with the pattern as shown in example. Display the
// resultant output word in the root.
// Example: Input: PCAP
// Output: PCCAAAPPPP

#include<stdio.h> 
#include<stdlib.h>
#include<mpi.h>

int main(int argc,char* argv[]){
    int size,rank;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int r, ans[4];
    char str[4];
    int t=rank+1;
    if(rank==0){
        printf("Enter elements : ");
        fgets(str, sizeof(str), stdin);
    }

    MPI_Scan(&t,&r,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    MPI_Gather(&r,1,MPI_INT,ans,1,MPI_INT,0,MPI_COMM_WORLD);
    int i=0;
    int j=0;
    if(rank==0){
        int temp=size*(size+1)/2;
        while(i<=temp){
            if(i==ans[j])
                j++;
            printf("%c",str[j]);
            i++;
        }
        printf("\n");
    }
    MPI_Finalize();
}

