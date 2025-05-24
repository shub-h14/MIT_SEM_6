%{
#include <stdio.h>
int pos = 0;
int neg = 0;
int fpos = 0;
int fneg = 0;
%}

%%

"-"[0-9]+\.[0-9]+ { fneg++; }
"-"[0-9]+ { neg++; }
[+]?[0-9]+\.[0-9]+ { pos++; }
[+]?[0-9]+ { fpos++; }

%%

int main(){
yylex();
printf("Positive are %d and negative are %d while float positive are %d and float negative are %d\n", pos, neg, fpos, fneg); }
int yywrap()
{
return 1;
}
