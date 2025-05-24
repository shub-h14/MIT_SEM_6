%{
#include <stdio.h>
int vow = 0;
int conso = 0;
%}

%%

[aeiouAEIOU] { vow++; }
[a-zA-Z] { conso++; }

%%

int main() {
    yylex();
    printf("Vowels are %d and consonants are %d\n", vow, conso);
    return 0;
}

int yywrap() {
    return 1;
}
