// To reverse the file contents and store in another file. Also display
// the size of file using file handling function.

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr, *fptr2;
    char filename[100], c;
    int n = 0;

    printf("Enter the filename to open for reading: ");
    scanf("%s", filename);

    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }

    fseek(fptr, 0, SEEK_END);
    n = ftell(fptr);
    rewind(fptr);

    printf("Enter the filename to open for writing: ");
    scanf("%s", filename);
    fptr2 = fopen(filename, "w+");
    if (fptr2 == NULL) {
        printf("Cannot open file for writing %s \n", filename);
        fclose(fptr);
        exit(0);
    }

    for (int i = n - 1; i >= 0; i--) {
        fseek(fptr, i, SEEK_SET);  
        c = fgetc(fptr);  
        fputc(c, fptr2);  
    }

    fclose(fptr);
    fclose(fptr2);

    printf("Contents copied to %s\n", filename);
    printf("File size was: %d bytes\n", n);

    return 0;
}

// Sample I/O:

// Enter the filename to open for reading: pasta.txt
// Enter the filename to open for writing: copypasta.txt
// Contents copied to copypasta.txt
// File size was: 1832 bytes
