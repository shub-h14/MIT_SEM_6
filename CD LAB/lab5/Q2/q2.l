%{
#include <stdio.h>
int words = 0;
int chars = 0;
int blanks = 0;
int lines = 0;
%}

%%

[a-zA-Z] {chars++; }
[" "] { blanks++, chars++, words++; }
[\n] { lines++; }

%%

int main() {
    yylex();
    printf("Chars are %d, lines are %d, words are %d and blanks are %d\n", chars, lines, words+1, blanks);
    return 0;
}

int yywrap() {
    return 1;
}
