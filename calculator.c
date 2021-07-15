#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXSIZE 100

int stack[MAXSIZE]; 
int top = -1; //堆疊的頂端
int empty();
void push(int);
int pop();
int calculate(char*);

int empty()  //判斷是否為空
{
    if(top==-1)
        return 1;
    else
        return 0;
}
void push(int data)
{
    if(top>=MAXSIZE)
        printf("stak is full\n");
    else
    {
        top++;
        stack[top] = data;
    }
}

int pop()
{
    int data;
    if(empty())
        printf("stack is empty\n");
    else
       {
           data = stack[top];
           top--;
       }
       return data;
}

int calculate(char *infix)
{
    
    int num = 0; //紀錄算式中數字
    char sign = '+'; // 紀錄數字前符號
    int i;
    int n = strlen(infix);  //infix length
    for(i=0;i<n;i++)
    {
        char c = infix[i];
        if(isdigit(c)) //如果是數字讀取到num裡

        {
            num = 10 * num + (c-48);  //轉數字
        }

        if(!isdigit(c) && c != ' ' || i==n-1)
        {
            switch(sign)
            {
                int pre;
                case '+':
                    push(num);
                    break;
                case '-':
                    push(-num);
                    break;
                case '*':
                    pre = stack[top];
                    pop();
                    push(pre*num);
                    break;
                case '/':
                    pre = stack[top];
                    pop();
                    push(pre/num);
                    break;
            }
            //更新符號和數字歸零
            sign = c;
            num = 0;
        }
        
    }

    int answer = 0;
    while(!empty())  //將剩下數自計算出
    {
        answer += stack[top];
        pop();
    }
    return answer;
}

int main(int argc,char **argv)
{
    char infix[MAXSIZE] = {'\0'};
    printf("Input algorithm: ");
    fgets(infix,MAXSIZE,stdin); 
    printf("%d",calculate(infix));
    return 0;
}