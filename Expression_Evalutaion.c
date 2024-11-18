#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

void push(Stack *stack, int value) {
    stack->data[++stack->top] = value;
}

int pop(Stack *stack) {
    return stack->data[stack->top--];
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int top(Stack *stack) {
    return stack->data[stack->top];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int evaluate(char *tokens) {
    int i;
    Stack values, ops;
    values.top = ops.top = -1;

    for (i = 0; i < strlen(tokens); i++) {
        if (tokens[i] == ' ')
            continue;
        else if (tokens[i] == '(') {
            push(&ops, tokens[i]);
        } else if (isdigit(tokens[i])) {
            int val = 0;
            while (i < strlen(tokens) && isdigit(tokens[i])) {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }
            push(&values, val);
            i--;
        } else if (tokens[i] == ')') {
            while (!isEmpty(&ops) && top(&ops) != '(') {
                int val2 = pop(&values);
                int val1 = pop(&values);
                char op = pop(&ops);
                push(&values, applyOp(val1, val2, op));
            }
            if (!isEmpty(&ops))
                pop(&ops);
        } else {
            while (!isEmpty(&ops) && precedence(top(&ops)) >= precedence(tokens[i])) {
                int val2 = pop(&values);
                int val1 = pop(&values);
                char op = pop(&ops);
                push(&values, applyOp(val1, val2, op));
            }
            push(&ops, tokens[i]);
        }
    }

    while (!isEmpty(&ops)) {
        int val2 = pop(&values);
        int val1 = pop(&values);
        char op = pop(&ops);
        push(&values, applyOp(val1, val2, op));
    }

    return pop(&values);
}

int main() {
    printf("%d\n", evaluate("10 + 2 * 6"));
    printf("%d\n", evaluate("100 * 2 + 12"));
    printf("%d\n", evaluate("100 * ( 2 + 12 )"));
    printf("%d\n", evaluate("100 * ( 2 + 12 ) / 14"));
    return 0;
}
