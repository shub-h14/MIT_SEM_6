// This is a single line comment
/*
THIS IS
A MULTI
LINE
COMMENT
*/
#include <stdio.h>
void main()
{
	FILE *fopen(), *fp;
	int c ;
	fp = fopen( “prog.c”, “r” ); //Comment
		
		c = getc( fp ) ;
	while ( c != EOF ) {
		putchar( c );
		c = getc ( fp );
	}
	/*
	MULTI
	LINE
	COMMENT
	*/
	fclose(fp );
}
