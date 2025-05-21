#include <stdio.h>
#include <stdlib.h>
int main() {
	FILE *fi, *fo;
	int c;
	fi = fopen("q2input.c", "r");
	if (fi == NULL) {
		printf("Cannot open file \n");
		exit(0); 
	}
	fo = fopen("q2output.c", "w");
	c = getc(fi);
	while (c != EOF) {
		if(c =='\"') {
			putc(c, fo);
			c = getc(fi);
			putc(c, fo);
			while(c != '\"') {
				c = getc(fi);
				putc(c, fo);
			}
		}
		else if(c == '#') {
			while(c != '\n')
				c = getc(fi);
		}
		else putc(c, fo);
		c = getc(fi);
	}
	fclose(fi);
	fclose(fo);
	return 0;
}
