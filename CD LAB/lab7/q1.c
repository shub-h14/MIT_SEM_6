#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"la.h"

tk ct;
FILE* fp;

void error(char* s) {
    printf("Syntax Error: Expected '%s' at row %d, col %d but found '%s'\n", s, ct.row, ct.col, ct.token_name);
    exit(1);
}

void check(char* s, int k) {
    if ((k == 1 && strncmp(ct.token_name, "id", 2) == 0) || (strcmp(ct.token_name, s) == 0)) {
        ct = getNextToken(fp);
    } else {
        error(s);
    }
}

void id_list() {
    if (strncmp(ct.token_name, "id", 2) == 0)
        ct = getNextToken(fp);
    if (strcmp(ct.token_name, ",") == 0) {
        check(",", 0);
        id_list();
    }
}

void dec() {
    if (strcmp(ct.token_name, "int") == 0 || strcmp(ct.token_name, "char") == 0) {
        ct = getNextToken(fp);
        id_list();
        check(";", 0);
        dec();
    } else {
        error("int or char");
    }
}

void ass() {
    if (strncmp(ct.token_name, "id", 2) == 0) {
        check("id", 1);
        check("=", 0);
        if (isdigit(ct.token_name[0])) {
            ct = getNextToken(fp);
        } else if (strncmp(ct.token_name, "id", 2) == 0) {
            ct = getNextToken(fp);
        } else {
            error("id or num");
        }
        check(";", 0);
    }
}

void program() {
    check("main", 0);
    check("(", 0);
    check(")", 0);
    check("{", 0);
    dec();
    ass();
    check("}", 0);
}

int main() {
    fp = fopen("test.c", "r");

    printf("The test case is : \n");
    char ch = fgetc(fp);
    while (ch != EOF) {
        printf("%c", ch);
        ch = fgetc(fp);
    }

    rewind(fp);

    ct = getNextToken(fp);
    program();

    printf("The grammer is accepted\n");
}
