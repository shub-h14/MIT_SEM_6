#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct token{
	char token_name[50];
	unsigned int row, col;
	char token_type[50];
}tk;

int getNextchar(FILE* fp, int* row, int* col){
	int c = getc(fp);

	*col = *col + 1;
	if(c=='\n'){
		*row = *row + 1;
		*col = 0;
	}
	//printf("%c row = %d col = %d\n", c, *row, *col);
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
            return 1;  // It's a keyword
        }
    }
    return 0;  // Not a keyword
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

        // Checking for comments
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

        // Check for whitespace and discard it
        if (c == ' ' || c == '\t') {
            c = getNextchar(fp, &row, &col);
            while (c == ' ' || c == '\t') c = getNextchar(fp, &row, &col);
        }

        // Handling and ignoring directives
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
            // printf("Hello\n");
            // Check for relational operators
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
