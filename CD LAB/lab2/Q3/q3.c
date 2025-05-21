#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *keywords[] = {"for", "if", "else", "while", "do", "break", "continue", "return", "int", "double", "float", "char", "long", "short", "sizeof", "typedef", "switch", "case", "struct", "const", "void", "exit"};

int isKeyword(const char* str){
	for(int i = 0;i<sizeof(keywords)/sizeof(char*);i++){
		if(strncmp(str,keywords[i],strlen(keywords[i])) == 0)
			return 1;
	}
	return 0;
}

void Upper(char *str,const int n){
	for(int i = 0;i<n;i++)
		str[i] = toupper(str[i]);
}

int main(){
	char temp[100];
	FILE *fi;
	int i = 0;
	char filename[100], c;
	fi = fopen("q3input.c", "r");
	if (fi == NULL) {
		printf("Cannot open file \n");
		exit(0); 
	}
	c = getc(fi);
	printf("Keywords are:\n");

	while(c != EOF){
		if(isalpha(c)){
			temp[i++] = c;
		}
		else{
			temp[i] = '\0';
			if(isKeyword(temp)){
				Upper(temp,i);
				printf("%s \n",temp);
			}
			i = 0;
		}
		c = getc(fi);
		
	}
	fclose(fi);
	return 0;
}
