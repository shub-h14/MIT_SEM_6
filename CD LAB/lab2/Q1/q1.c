#include <stdio.h>
#include <stdlib.h>
int main() {
	FILE *fi, *fo;
	int c;
	fi = fopen("q1input.c", "r");
	if (fi == NULL) {
		printf("Cannot open file \n");
		exit(0); 
	}
	fo = fopen("q1output.c", "w");
	c = getc(fi);
	while (c != EOF) {
		if(c == '\t' || c == ' ') {
			putc(' ', fo);
			while(c == ' ' || c == '\t')
				c = getc(fi);
			putc(c, fo);
		}
		else putc(c, fo);
		c = getc(fi);
	}
	fclose(fi);
	fclose(fo);
	return 0;
}
