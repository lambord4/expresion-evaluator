#include<stdio.h>

char expr[20];//array to store entered expression
char stack[20];//store the postfix expression
int precedence(char a, char b) {//returns true if precedence of operator a is more or equal to than that of b
    return ((a == '+') || (a == '-')) && ((b == '*') || (b == '/')) ? 0 : 1;
}

int i;
int ctr;
int topOfValueStack = -1;
int topOperatorStack = -1;

int applyOperator(int a, int b, char oper) {
    switch (oper) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
            break;//return result of evaluation
        case '/':
            return a / b;
        default:
            return 0;
    }
}

void postfixConvert() {
    char topsymb, operatorStack[20];
    ctr = 0;
    while (expr[ctr] != '\0') {
        if (expr[ctr] >= '0' && expr[ctr] <= '9') {
            int val = 0, step = 1;
            while (expr[ctr] != '\0' && isdigit(expr[ctr])) {
                val = val * step + (int) (expr[ctr] - '0');
                step *= 10;
                ctr++;
            }
            stack[++topOfValueStack] = val + '0';
            ctr--;
        } else {
            while (topOperatorStack >= 0 && precedence(operatorStack[topOperatorStack], expr[ctr])) {
                topsymb = operatorStack[topOperatorStack--];
                stack[++topOfValueStack] = topsymb;
            }
            operatorStack[++topOperatorStack] = expr[ctr];
        }
        ctr++;
    }
    while (topOperatorStack >= 0) {
        stack[++topOfValueStack] = operatorStack[topOperatorStack--];
    }
}

int main() {
    printf("Enter the Expression\n");
    scanf("%s", expr);
    postfixConvert();
    int operand1, operand2, temp;
    ctr = 0;
    int result[2];
    int rTop = -1;
    while (stack[ctr] != '\0') {
        temp = (int) (stack[ctr] - '0');
        if (temp >= 0)
            result[++rTop] = temp;
        else {
            operand1 = result[rTop--];
            operand2 = result[rTop--];
            result[++rTop] = applyOperator(operand2, operand1, stack[ctr]);
        }
        ctr++;
    }
    printf("The result of the expression is: %d\n", result[0]);
    getchar();
}
