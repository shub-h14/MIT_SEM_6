#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int DJB2Hash(const void *key, int len) {
    unsigned long hash = 5381; 
    const unsigned char *data = (const unsigned char *)key;

    for (int i = 0; i < len; i++) {
        hash = ((hash << 5) + hash) + data[i];
    }

    return (int)(hash & 0x7FFFFFFF);
}


typedef struct token{
	char token_name[50];
	unsigned int row, col;
	char token_type[50];
}tk;

typedef struct symbol{
    char name[50];
    char type[30];
    int size;
    struct symbol* next;
}sy;

int d_size=0;
char dbuf[30]="";
typedef struct {
    char type_name[30]; 
    int size;           
} DataType;
DataType data_types[] = {
    {"int", 4},
    {"float", 4},
    {"double", 8},
    {"char", 1},
    {"void", 0},
    {"long", 8},
    {"short", 2},
    {"unsigned", 4}
};
void updateDataTypeSize(const char* type_name) {
    int num_types = sizeof(data_types) / sizeof(data_types[0]);
    
    for (int i = 0; i < num_types; i++) {
        if (strcmp(data_types[i].type_name, type_name) == 0) {
            strcpy(dbuf,data_types[i].type_name);
            d_size=data_types[i].size;
        }
    }
}


sy* symbol_table[10]={NULL};
int k=1;
int getNextchar(FILE* fp, int* row, int* col){
	int c = getc(fp);

	*col = *col + 1;
	if(c=='\n'){
		*row = *row + 1;
		*col = 0;
	}
	return c;
}

int isSymbol(char c) {
    char symbols[] = "+-*/%=<>&|^!~(){}[],;";
    for (int i = 0; i < strlen(symbols); i++) {
        if (c == symbols[i]) {
            return 1;
        }
    }
    return 0;
}

int isKeyword(const char *str) {
    const char *keywords[] = {
        "int", "float", "double", "char", "void", "return", "if", "else",
        "while", "for", "break", "continue", "switch", "case", "default",
        "struct", "typedef", "long", "short"
    };
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;  
        }
    }
    return 0;  
}

int row=1;
int col=0;

tk getNextToken(FILE* fp) {
    int c;
    int isDirective = 0;
    tk token;
    c = getNextchar(fp, &row, &col);

    while (1) {
        if (c == '\n')
            c = getNextchar(fp, &row, &col);

        if (c == '/') {
            int cb;
            cb = getNextchar(fp, &row, &col);
            if (cb == '/') {
                while (cb != '\n') cb = getNextchar(fp, &row, &col);
                c = cb;
            } else if (cb == '*') {
                do {
                    while (c != '*') c = getNextchar(fp, &row, &col);
                    c = getNextchar(fp, &row, &col);
                } while (c != '/');
            }
        }

        if (c == ' ' || c == '\t') {
            c = getNextchar(fp, &row, &col);
            while (c == ' ' || c == '\t') c = getNextchar(fp, &row, &col);
        }

        if (c == '#') {
            const char *directives[] = {
                "define", "include", "if", "ifdef", "ifndef", "else",
                "elif", "endif", "undef", "pragma", "error", "warning"
            };
            int numDirectives = sizeof(directives) / sizeof(directives[0]);
            int i = 0;
            int cb;
            char buf[50];
            cb = getNextchar(fp, &row, &col);

            while (cb != ' ' && cb != '\n' && cb != EOF) {
                buf[i] = cb;
                i++;
                cb = getNextchar(fp, &row, &col);
            }
            buf[i] = '\0';
            for (int j = 0; j < numDirectives; j++) {
                int len = strlen(directives[j]);
                if (strncmp(directives[j], buf, len) == 0) {
                    isDirective = 1;
                    break;
                }
            }
            if (isDirective) {
                c = getNextchar(fp, &row, &col);
            }
        }

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            token.row = row;
            token.col = col;
            int i = 0;
            while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                token.token_name[i++] = c;
                c = getNextchar(fp, &row, &col);
            }
            ungetc(c, fp);
            col--;
            token.token_name[i] = '\0';

            if (isKeyword(token.token_name)) {
                strcpy(token.token_type, token.token_name);
            } else {
                strcpy(token.token_type, "id");
            }

            return token;
        }

        if (c >= '0' && c <= '9') {
            token.row = row;
            token.col = col;
            int i = 0;
            while (c >= '0' && c <= '9') {
                token.token_name[i++] = c;
                c = getNextchar(fp, &row, &col);
            }
            ungetc(c, fp);
            col--;
            token.token_name[i] = '\0';
            strcpy(token.token_type, "num");
            return token;
        }

        if (isSymbol(c)) {
            token.row = row;
            token.col = col;
            token.token_name[0] = c;
            if (c == '=' || c == '<' || c == '>' || c == '!') {
                int nextChar = getNextchar(fp, &row, &col);
                if (nextChar == '=') {
                    token.token_name[1] = nextChar;
                    token.token_name[2] = '\0';

                    if (c == '=') strcpy(token.token_type, "EQUALS");
                    if (c == '<') strcpy(token.token_type, "LESSTHAN_EQ");
                    if (c == '>') strcpy(token.token_type, "GREATERTHAN_EQ");
                    if (c == '!') strcpy(token.token_type, "NOT_EQ");

                    return token;
                } else {
                    ungetc(nextChar, fp);
                    col--;
                    token.token_name[1] = '\0';
                    if(c=='=') strcpy(token.token_type,"=");
                    if (c == '<') strcpy(token.token_type, "LESSTHAN");
                    if (c == '>') strcpy(token.token_type, "GREATERTHAN");
                    if (c == '!') strcpy(token.token_type, "NOT");
                    return token;
                }
            }else{
                token.token_name[1] = '\0';
                token.token_type[0] = c;
                token.token_type[1] = '\0';
            }
            return token;
        }

        if (c == EOF)
            break;
    }

    token.token_name[0] = '\0';
    return token;
}


int main(){
    int prev_index;
	FILE *fp;
	fp = fopen("input.c", "r");
	if(fp==NULL){
		printf("Cannot open file\n");
		exit(0);
	}
	tk temp;
    int flag=0;
    printf("\n------------ TOKEN DETAILS ------------\n");
	while(1){
		temp = getNextToken(fp);
		if(temp.token_name[0]=='\0')
			break;
        if(strcmp(temp.token_type,"[")==0)
            flag=1;
        if((strcmp(temp.token_type,"num")==0)&&(flag==1)){
            sy* temppp=symbol_table[prev_index];
            while(temppp->next!=NULL)
                temppp=temppp->next;
            temppp->size=d_size*atoi(temp.token_name);
            flag=0;
        }
        if(strcmp(temp.token_type,"id")==0){
            snprintf(temp.token_type + strlen(temp.token_type), sizeof(temp.token_type) - strlen(temp.token_type), "%d", k);
            k++;
            int hash=DJB2Hash(temp.token_name,strlen(temp.token_name));
            int index=hash%10;
            printf("\nToken hash index: %d\n", index);
            sy* helper=symbol_table[index];
            sy* tempp=(sy*)malloc(sizeof(sy));
            int yes=1;
            if(helper!=NULL){
                sy* prev;
                while(helper!=NULL){
                    if(strcmp(helper->name,temp.token_name)==0){
                        yes=0;
                    }
                    prev=helper;
                    helper=helper->next;
                }
                if(yes==1)
                    prev->next=tempp;
            }
            if(yes==1){
                if(helper==NULL){
                    symbol_table[index]=tempp;
                }
                strcpy(tempp->name,temp.token_name);
                strcpy(tempp->type,dbuf);
                tempp->size=d_size;
                tempp->next=NULL;
                prev_index=index;
            }
        }
        updateDataTypeSize(temp.token_name);
		printf("<Token: %s, Row: %d, Column: %d, Name: %s>\n", temp.token_type, temp.row, temp.col,temp.token_name);
	}
	fclose(fp);
    printf("\n------------ SYMBOL TABLE ------------\n");
    for (int i = 0; i < 10; i++) {
        printf("Index %d: ", i);
        if(symbol_table[i] != NULL) {  
            sy* temp = symbol_table[i];
            while (temp != NULL) {
                printf("<Name: %s, Type: %s, Size: %d>\n", temp->name, temp->type, temp->size);
                temp = temp->next;
            }
        } else {
            printf("Empty\n");
        }
    }
	return 0;
}
