#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#define MAX 1000


void intopostfix(char*, char*); // 中序轉後序 
int priority(char); // 運算子優先權
int compute(char* ); //計算出數值

int main(int argc, char *argv[]) { 
    char infix[MAX] = {'\0'}; 
    char postfix[MAX]= {'\0'};

 for(int i=1;i<argc;i++)
 {
     strcat(infix,argv[i]);
     strcat(infix," ");
 }
//printf("輸入算式："); 
    //scanf("%[^\n]",infix);  //直到輸出enter停止輸入
    intopostfix(infix, postfix);
    //printf("infix : %s",infix);
   //printf("postfx : %s\n",postfix);
    printf("answer : %d\n",compute(postfix));
    return 0; 
} 

int priority(char op) { 
    switch(op) { 
        case '+':
         case '-': 
            return 1;
        case 'x':
         case '/':
             return 2;
        default: 
            return 0;
    } 
} 

void intopostfix(char* infix, char* postfix) 
{ 

    char stack[MAX] = {'\0'};
    int i, j, top;
    for(i = 0, j = 0, top = 0; infix[i] != '\0';i++) 
    {
    	if(infix[i]=='-'&&isdigit(infix[i+1]))  //if there is a negative sign before the number, set a negative sign before number in postfix
        {
            postfix[j++] = '-';
            i++;
            
        }
    	
    	if(i==0)  //if negative sign in the first car
		{
			if(infix[i]=='-')
            {
            	postfix[j++] = '-';
            	i++;
            }
		}

    switch(infix[i])
        {
            case ' ':
                break;
            case '(':              
                stack[++top] = infix[i];
				if(infix[i+1]=='-')  
            	{
            		postfix[j++] = '-';
            		i++;
            	}
                break; 
                
                
            case '+':
            case 'x':
            case '/': 
            case '-':
                while(priority(stack[top]) >= priority(infix[i])) 
                { 
                	if(postfix[j-1] != ' ')
	            		{
	            			postfix[j++] = ' ';
						}
	                postfix[j++] = stack[top--];
                } 
                postfix[j++] = ' '; 
                stack[++top] = infix[i];  
                
                
                if(infix[i+1]=='-')  
            	{
            		postfix[j++] = '-';
            		i++;
            	}
                
                break;


            case ')': 
                while(stack[top] != '(')       
                { 
                	postfix[j++] = ' ';
                    postfix[j++] = stack[top--];
                } 
                top--;  
                break;
                
            default:
            	postfix[j++] = infix[i];
        }
    } 
    while(top > 0) { 
    	postfix[j++] = ' ';
        postfix[j++] = stack[top--];    
    }
}

int compute(char *postfix)
{	char temp[MAX] = {'\0'};
    int stack[MAX] = {'\0'};
    int top,i,j;
    for(i=0,top=0;postfix[i]!='\0';i++)
    {
       switch(postfix[i])
       {
       	case '+': case '-':
       		if(postfix[i+1]>47 && postfix[i+1]<58)
       		{
       			for(j=0;postfix[i]!=' ';i++,j++)
				   {
				   		temp[j] = postfix[i];	
				   }
				   stack[++top] = atol(temp);
				   memset(temp,'\0',sizeof(temp));
				   break;
			}
			if(postfix[i]=='+')
				stack[top-1] = stack[top-1] + stack[top];
			else
				stack[top-1] = stack[top-1] - stack[top];
			top--;
			break;
			
		case '/':
			stack[top-1] = stack[top-1] / stack[top];
			top--;
			break;
		case 'x':
			stack[top-1] = stack[top-1] * stack[top];
			top--;
			break;
		case ' ':
			break;
		default:
			for(j=0;postfix[i] != ' ';i++,j++)
			{
				temp[j] = postfix[i];
			}
			stack[++top] = atol(temp);
			memset(temp,'\0',sizeof(temp));
	   }
	   
	}
	return stack[top];	
}