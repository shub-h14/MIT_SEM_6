%{
int num = 0;
%}

%%

[0-9]+ { num = atoi(yytext); }

%%

int main(){
    yylex();
    printf("Hexadecimal number is %X\n",num);
}

int yywrap(){
    return 1;
} 
