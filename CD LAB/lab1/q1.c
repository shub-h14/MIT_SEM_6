// 1. To count the number of lines and characters in a file.

#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *fptr;
	char filename[100], c;
	int dline_count = 0, char_count = 0;

	printf("Enter the filename to open for reading: ");
	scanf("%s", filename);

	fptr = fopen(filename, "r");
	if (fptr == NULL) {
		printf("Cannot open file %s \n", filename);
		exit(0);
	}

	c = fgetc(fptr);

	while (c != EOF) {
		if(c == '\n')
			dline_count++;
		else
			char_count ++;
		c = fgetc(fptr);
	}

	if (char_count > 0 && c == EOF) {
        dline_count++;
    } // tackle last line if it ends with a newline or not, check and count it towards the total

	fclose(fptr);
	printf("Number of lines is: %d \nNumber of characters is: %d\n", dline_count, char_count);
	return 0;
}

// Sample I/O:

// Enter the filename to open for reading: pasta.txt
// Number of lines is: 25 
// Number of characters is: 1808
