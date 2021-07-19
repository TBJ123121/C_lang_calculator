// add_op := + | -
//   mul_op := * | /
//   digits := {+|-} [0..9] {[0..9]}
//   expr   := term {add_op term}
//   term   := factor {mul_op factor}
//   factor := digits | '(' expr ')'


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef int calint;
calint expr(void);
char token;

void match(char expected)
{
    if(token==expected)
    {
        token = getchar();
        return;
    }
    fprintf(stderr,"Expected %c, got %c", expected, token);
    exit(1);
}

void error(const char *msg) {
    fputs(msg, stderr);
    exit(1);
}

calint factor()
{
    calint value;
    if(token=='(')
    {
        match('(');
        value = expr();
        match(')');
    }
    else if(isdigit(token)||token=='+'||token=='-')
    {
        ungetc(token, stdin);
        scanf("%d", &value);

        token = getchar();
    }
    else 
    {
        error("error");
    }
    return value;
}

calint term()
{
    calint value = factor();
    while(token=='*'||token=='/')
    {
        switch(token)
        {
            case '*':
                match('*');
                value*=factor();
                break;
            case '/':
                match('/');
                value/=factor();
                break;
            default:
                error("error");
        }
    }
    return value;
}

calint expr()
{
    calint value = term();
    if(token=='+'||token=='-')
    {
        switch(token)
        {
            case '+':
                match('+');
                value+=term();
                break;
            case '-':
                match('-');
                value-=term();
                break;
            default:
            error("error");
        }
    }
    return value;
}

int main(int argc, char *argv[])
{
    token = getchar();
    calint result = expr();
    printf("reslut: %d\n",result);
}