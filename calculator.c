
#include <stdio.h>
#include <stdlib.h>

double factor(char *expr, char **end) {
    double exp(char*, char**);
    double res=0;
    if (*(*end=expr) == '(') {
        res = exp(*end+1, end);
        if (**end == ')') ++*end;
    } else { res=strtod(*end, end); }
    return res;
}

double term(char* expr, char** end) {
    double res = factor(expr, end);
    while (**end=='*' || **end=='/') 
        (**end=='*')? (res*=factor(*end+1, end)): (res/=factor(*end+1, end));
    return res;
}

double exp(char* expr, char** end) { 
    double res = term(expr, end);
    while (**end=='+' || **end=='-') 
        res +=(**end=='+')? term(*end+1, end): -term(*end+1, end);
    return res;
}

int main(int argc, char *argv[]) {
    char expr[128]={0}, *pos=0;
    int i;
    for (i=1;i<argc;i++)
    {
        strcat(expr,argv[i]);
    }
    // printf("Input : ");
    // scanf("%s", expr);
    printf("Ans : %f\n", exp(expr, &pos));
}