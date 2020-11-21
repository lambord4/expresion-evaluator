// this evaluator will work with arithmetic operations(+,-,*,/) on a single digit operand length under 20 chars max
// paranteses '()' aren't included as well.
#include<stdio.h>

char expr[20];
char stack[20];
int precedence(char a, char b) {
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
            // add while loop here for merging multidigit operands
            stack[++topOfValueStack] = expr[ctr];
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
    char temp;
    int operand1, operand2;
    ctr = 0;
    int result[2];
    int rTop = -1;
    while (stack[ctr] != '\0') {
        temp = stack[ctr];
        if (temp >= '0' && temp <= '9')
            result[++rTop] = (int) (temp - '0');
        else {
            operand1 = result[rTop--];
            operand2 = result[rTop--];
            result[++rTop] = applyOperator(operand2, operand1, temp);
        }
        ctr++;
    }
    printf("The result of the expression is: %d\n", result[0]);
    getchar();
}
