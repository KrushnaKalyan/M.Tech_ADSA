//Q3-a  Infix to postfix

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    if(top == -1) return '\0';
    return stack[top--];
}

char peek() {
    if(top == -1) return '\0';
    return stack[top];
}

int precedence(char c) {
    if(c == '+' || c == '-') return 1;
    if(c == '*' || c == '/') return 2;
    return 0;
}

void infixToPostfix(char infix[], char postfix[]) {
    int i = 0, j = 0;
    char c;
    while(infix[i] != '\0') {
        c = infix[i];
        if(isalnum(c)) postfix[j++] = c;
        else if(c == '(') push(c);
        else if(c == ')') {
            while(top != -1 && peek() != '(') postfix[j++] = pop();
            pop();
        } else {
            while(top != -1 && precedence(peek()) >= precedence(c)) postfix[j++] = pop();
            push(c);
        }
        i++;
    }
    while(top != -1) postfix[j++] = pop();
    postfix[j] = '\0';
}

int main() {
    char infix[100], postfix[100];
    printf("Enter infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    return 0;
}

