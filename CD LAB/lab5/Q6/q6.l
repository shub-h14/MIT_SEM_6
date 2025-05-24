%{
#include<stdio.h>
FILE *in,*out;
%}

%%
[A-Z] {fputc(yytext[0]+32,out);}
\/\/.*|\/\*([^*]|\*+[^*/])*\*\/ {fputs(yytext,out);}
(.|\n) {fputs(yytext,out);}
%%

int yywrap(){
    return 1;
}

int main(){
    in=fopen("input.c","r");
    yyin=in;
    out=fopen("output.c","w");
    yylex();
    yywrap();
    fclose(in);
    fclose(out);
}
