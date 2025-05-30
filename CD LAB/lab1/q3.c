// That merges lines alternatively from 2 files and stores it in a resultant file.

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr1, *fptr2, *fptr3, *fptr_dest;
    char filename[50], c1, c2;
    printf("Enter the first file to be opened: ");
    scanf("%s", filename);
    fptr1 = fopen(filename, "r");
    if (!fptr1){
        printf("Cannot open file %s \n", filename);
        exit(0);
    }

    printf("Enter the second file to be opened: ");
    scanf("%s", filename);
    fptr2 = fopen(filename, "r");
    if (!fptr2){
        printf("Cannot open file %s \n", filename);
        exit(0);
    }

    printf("Enter the destination file: ");
    scanf("%s", filename);
    fptr_dest = fopen(filename, "r");
    if (!fptr_dest){
        printf("Cannot open file %s \n", filename);
        exit(0);
    }

    fptr3 = fopen(filename, "w+");
    c1 = fgetc(fptr1);
    c2 = fgetc(fptr2);

    while (c1 != EOF || c2 != EOF) {
        while (c1 != '\n' && c1 != EOF) {
            fputc(c1, fptr3);
            c1 = fgetc(fptr1);
        }
        if (c1 == '\n')
            fputc(c1, fptr3);
        c1 = fgetc(fptr1);
        while (c2 != '\n' && c2 != EOF) {
            fputc(c2, fptr3);
            c2 = fgetc(fptr2);
        }
        if (c2 == '\n')
            fputc(c2, fptr3);
        c2 = fgetc(fptr2);
    }

    printf("Done!\n");

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
    return 0;
}

// Sample I/O:

// Enter the first file to be opened: pasta.txt
// Enter the second file to be opened: copypasta.txt
// Enter the destination file: dest.txt
// Done!
