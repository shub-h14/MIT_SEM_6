#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include</home/student2/Documents/220905236/Lab7/la.h>

int string_in_array(char *str, char *arr[], int size);
void error(char* s);
void check(char* s, int k);
void mulop();
void addop();
void relop();
void dprime();
void stat_list();
void factor();
void term();
void tprime();
void sprime();
void simple_exp();
void eprime();
void expn();
void stat();
void dec_stat();
void id_list();
void dec();
void ass();
void program();

tk ct;
FILE* fp;

int string_in_array(char *str, char *arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(str, arr[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void error(char* s){
    printf("Syntax Error: Expected '%s' at row %d, col %d but found '%s'\n",s,ct.row,ct.col,ct.token_name);
    exit(1);
}

void check(char* s,int k){
    if((k==1&&strncmp(ct.token_name,"id",2)==0)||(strcmp(ct.token_name,s)==0)){
        ct=getNextToken(fp);
    }
    else
        error(s);
}

void mulop(){
    if(strcmp(ct.token_name,"*")==0)
        check("*",0);
    else if(strcmp(ct.token_name,"/")==0)
        check("/",0);
    else if(strcmp(ct.token_name,"%")==0)
        check("%",0);
    else
        error("* or / or %");
}

void addop(){
    if(strcmp(ct.token_name,"+")==0)
        check("+",0);
    else if(strcmp(ct.token_name,"-")==0)
        check("-",0);
    else
        error("+ or -");
}

void relop(){
    if(strcmp(ct.token_name,"==")==0)
        check("==",0);
    else if(strcmp(ct.token_name,"!=")==0)
        check("!=",0);
    else if(strcmp(ct.token_name,"<=")==0)
        check("<=",0);
    else if(strcmp(ct.token_name,">=")==0)
        check(">=",0);
    else if(strcmp(ct.token_name,">")==0)
        check(">",0);
    else if(strcmp(ct.token_name,"<")==0)
        check("<",0);
    else
        error("relop");
}

void dprime(){
    if(strcmp(ct.token_name,"else")==0){
        check("else",0);
        check("{",0);
        stat_list();
        check("}",0);
    }
}

void stat_list(){
    if((strncmp(ct.token_name,"id",2)==0)||(strcmp(ct.token_name,"if")==0)){
        stat();
        stat_list();
    }
}

void factor(){
    if((strncmp(ct.token_name,"id",2)==0)||(isdigit(ct.token_name[0])))
        ct=getNextToken(fp);
    else
        error("id or num");
}

void term(){
    factor();
    tprime();
}

void tprime(){
    char* m[]={"*","/","%"};
    if(string_in_array(ct.token_name,m,3)){
        mulop();
        factor();
        tprime();
    }
}

void sprime(){
    char* m[]={"+","-"};
    if(string_in_array(ct.token_name,m,2)){
        addop();
        term();
        sprime();
    }
}

void simple_exp(){
    term();
    sprime();
}

void eprime(){
    char* m[]={"==","!=","<=",">=","<",">"};
    if(string_in_array(ct.token_name,m,6)){
        relop();
        simple_exp();
    }
}

void expn(){
    simple_exp();
    eprime();
}

void stat(){
    if(strncmp(ct.token_name,"id",2)==0){
        ass();
        check(";",0);
    }
    else
        dec_stat();
}

void dec_stat(){
    check("if",0);
    check("(",0);
    expn();
    check(")",0);
    check("{",0);
    stat_list();
    check("}",0);
    dprime();
}

void id_list(){
    if(strncmp(ct.token_name,"id",2)==0){
        ct=getNextToken(fp);
        if(strcmp(ct.token_name,",")==0){
            check(",",0);
            id_list();
        }
        else if(strcmp(ct.token_name,"[")==0){
            check("[",0);
            if(isdigit(ct.token_name[0])){
                ct=getNextToken(fp);
                check("]",0);
                if(strcmp(ct.token_name,",")==0){
                    check(",",0);
                    id_list();
                }
            }
        }
    }else
        error("id");
}

void dec(){
    if(strcmp(ct.token_name,"int")==0||strcmp(ct.token_name,"char")==0){
        ct=getNextToken(fp);
        id_list();
        check(";",0);
        dec();
    }
}

void ass(){
    check("id",1);
    check("=",0);
    expn();
}

void program(){
    check("main",0);
    check("(",0);
    check(")",0);
    check("{",0);
    dec();
    stat_list();
    check("}",0);
}

int main(){
    fp=fopen("test1.c","r");

    printf("The test case is : \n");
    char ch=fgetc(fp);
    while(ch!=EOF){
        printf("%c",ch);
        ch=fgetc(fp);
    }

    rewind(fp);

    ct=getNextToken(fp);
    program();

    printf("The grammer is accepted\n");
}
