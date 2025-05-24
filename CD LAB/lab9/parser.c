#include<stdio.h>
#include<stdlib.h>
#include<string.h>
enum Action {
    Error,
    Shift,
    Reduce,
    Accept
};
struct action_entry{
    enum Action act;
    int dest;
};
char term[]={'+','*','(',')','i','$'};
struct action_entry parse_table[12][6];
int redlen[7]={1,3,1,3,1,3,1};
char nonterms[]={'E','T','F'};
char prod[]={'S','E','E','T','T','F','F'};
int goto_table[12][3]={{1,2,3},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}
                        ,{8,2,3},{-1,-1,-1},{-1,9,3},{-1,-1,10}
                        ,{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}};
void init_table()
{
    for(int i=0;i<12;i++)for(int j=0;j<6;j++)parse_table[i][j].act=Error;
    parse_table[0][2].act=Shift;parse_table[0][2].dest=4;
    parse_table[0][4].act=Shift;parse_table[0][4].dest=5;
    parse_table[1][0].act=Shift;parse_table[1][0].dest=6;
    parse_table[1][5].act=Accept;
    parse_table[2][0].act=Reduce;parse_table[2][0].dest=2;
    parse_table[2][1].act=Shift;parse_table[2][1].dest=7;
    parse_table[2][3].act=Reduce;parse_table[2][3].dest=2;
    parse_table[2][5].act=Reduce;parse_table[2][5].dest=2;
    parse_table[3][0].act=Reduce;parse_table[3][0].dest=4;
    parse_table[3][1].act=Reduce;parse_table[3][1].dest=4;
    parse_table[3][3].act=Reduce;parse_table[3][3].dest=4;
    parse_table[3][5].act=Reduce;parse_table[3][5].dest=4;
    parse_table[4][2].act=Shift;parse_table[4][2].dest=4;
    parse_table[4][4].act=Shift;parse_table[4][4].dest=5;
    parse_table[5][0].act=Reduce;parse_table[5][0].dest=6;
    parse_table[5][1].act=Reduce;parse_table[5][1].dest=6;
    parse_table[5][3].act=Reduce;parse_table[5][3].dest=6;
    parse_table[5][5].act=Reduce;parse_table[5][5].dest=6;
    parse_table[6][2].act=Shift;parse_table[6][2].dest=4;
    parse_table[6][4].act=Shift;parse_table[6][4].dest=5;
    parse_table[7][2].act=Shift;parse_table[7][2].dest=4;
    parse_table[7][4].act=Shift;parse_table[7][4].dest=5;
    parse_table[8][0].act=Shift;parse_table[8][0].dest=6;
    parse_table[8][3].act=Shift;parse_table[8][3].dest=11;
    parse_table[9][0].act=Reduce;parse_table[9][0].dest=1;
    parse_table[9][1].act=Shift;parse_table[9][1].dest=7;
    parse_table[9][3].act=Reduce;parse_table[9][3].dest=1;
    parse_table[9][5].act=Reduce;parse_table[9][5].dest=1;
    parse_table[10][0].act=Reduce;parse_table[10][0].dest=3;
    parse_table[10][1].act=Reduce;parse_table[10][1].dest=3;
    parse_table[10][3].act=Reduce;parse_table[10][3].dest=3;
    parse_table[10][5].act=Reduce;parse_table[10][5].dest=3;
    parse_table[11][0].act=Reduce;parse_table[11][0].dest=5;
    parse_table[11][1].act=Reduce;parse_table[11][1].dest=5;
    parse_table[11][3].act=Reduce;parse_table[11][3].dest=5;
    parse_table[11][5].act=Reduce;parse_table[11][5].dest=5;
}
void remake(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '$') {
            str[i+1]='\0';
            break;
        }
        if (str[i] == 'i' && str[i+1] == 'd') {
            for (int j = i+2; str[j] != '\0'; j++)str[j-1] = str[j];
        }
    }
}
void parse(char *input){
    int stack[100];
    char symbol[100];
    symbol[0]='$';
    stack[0]=0;
    int index;
    int top_symbol=0,top_stack=0;
    int ptr=0;
    while(1)
    {
        int present=stack[top_stack];
        char sym=input[ptr];
        int terminal;
        for(terminal=0;terminal<6;terminal++){
            if(sym==term[terminal])
                break;
        }

        if(terminal==6)
        {
            printf("\nUnkown term at %d\n",ptr);
            break;
        }
        if(parse_table[present][terminal].act==Shift)
        {
            top_stack++;
            top_symbol++;
            symbol[top_symbol]=sym;
            stack[top_stack]=parse_table[present][terminal].dest;
            ptr++;
            printf("Shift %d\n",stack[top_stack]);
        }
        else if(parse_table[present][terminal].act==Reduce)
        {
            top_symbol=top_symbol-redlen[parse_table[present][terminal].dest];
            top_stack=top_stack-redlen[parse_table[present][terminal].dest];
            top_stack++;
            top_symbol++;
            symbol[top_symbol]=prod[parse_table[present][terminal].dest];
            int got,k;
            for(k=0;k<3;k++)
                if(symbol[top_symbol]==nonterms[k])
                    break;
            if(goto_table[stack[top_stack-1]][k]==-1)
            {
                printf("Parsing Failed\n");
                break;
            }
            stack[top_stack]=goto_table[stack[top_stack-1]][k];
            printf("Reduce %d going to %d\n",parse_table[present][terminal].dest,stack[top_stack]);
        }
        else if(parse_table[present][terminal].act==Accept)
        {
            printf("\nParsed successfully\n");
            break;
        }
        else if(parse_table[present][terminal].act==Error)
        {
            printf("\nParsing failed\n");
            break;
        }
        printf("Stack:");
        for(int a=0;a<=top_stack;a++)
            printf("%d,",stack[a]);
        printf("\b Symbol:");
        for(int a=0;a<=top_symbol;a++)
            printf("%c",symbol[a]);
        printf(" input:%s ",input+ptr);
    }
}
void main()
{
    char str[100];
    init_table();
    scanf("%s",str);
    remake(str);
    parse(str);
}
