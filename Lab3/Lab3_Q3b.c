//Q3-b Evaluate postfix
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int main() {
    char postfix[200];
    int stack[MAX], top = -1;
    printf("Enter postfix expression (use space between numbers/operators): ");
    fgets(postfix, sizeof(postfix), stdin);
    char *token = strtok(postfix, " \n");
    while(token != NULL) {
        if(isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) stack[++top] = atoi(token);
        else {
            int b = stack[top--];
            int a = stack[top--];
            if(token[0] == '+') stack[++top] = a + b;
            else if(token[0] == '-') stack[++top] = a - b;
            else if(token[0] == '*') stack[++top] = a * b;
            else if(token[0] == '/') stack[++top] = a / b;
        }
        token = strtok(NULL, " \n");
    }
    printf("Evaluated result: %d\n", stack[top]);
    return 0;
}

