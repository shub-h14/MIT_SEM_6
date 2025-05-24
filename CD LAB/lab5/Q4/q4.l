%{
#include <stdio.h>
int sf = 0;
int pf = 0;
%}

%%
"scanf" { sf++; fwrite("READ", 1, 4, yyout); }
"printf" { pf++; fwrite("WRITE", 1, 5, yyout); }
[ \t\n]   ;
. { fwrite(yytext, 1, yyleng, yyout); }

%%

int main(int argc, char **argv) {
    yyin = fopen("input.c", "r");
    yyout = fopen("output.c", "w+");
    yylex();
    printf("Number of scanfs are %d and printfs are %d\n", sf, pf);
    return 0;
}

int yywrap() {
    return 1;
}
