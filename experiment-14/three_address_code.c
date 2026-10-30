#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef struct { char value[32]; } Item;

static int precedence(char op) { return op == '+' || op == '-' ? 1 : 2; }

int main(int argc, char **argv)
{
    char expression[256], postfix[256], operators[128];
    int output = 0, top = 0, i;
    Item values[128];
    int value_top = 0, temporary = 1;

    if (argc > 1) strncpy(expression, argv[1], sizeof(expression) - 1);
    else { printf("Expression: "); if (!fgets(expression, sizeof(expression), stdin)) return 1;
           expression[strcspn(expression, "\r\n")] = '\0'; }
    expression[sizeof(expression) - 1] = '\0';
    for (i = 0; expression[i]; i++) {
        if (isspace((unsigned char)expression[i])) continue;
        if (isalnum((unsigned char)expression[i])) postfix[output++] = expression[i];
        else if (expression[i] == '(') operators[top++] = expression[i];
        else if (expression[i] == ')') {
            while (top && operators[top - 1] != '(') postfix[output++] = operators[--top];
            if (top) top--;
        } else {
            while (top && operators[top - 1] != '(' &&
                   precedence(operators[top - 1]) >= precedence(expression[i]))
                postfix[output++] = operators[--top];
            operators[top++] = expression[i];
        }
    }
    while (top) postfix[output++] = operators[--top];
    postfix[output] = '\0';
    for (i = 0; postfix[i]; i++) {
        if (isalnum((unsigned char)postfix[i])) {
            values[value_top].value[0] = postfix[i]; values[value_top++].value[1] = '\0';
        } else {
            char temp[32];
            snprintf(temp, sizeof(temp), "t%d", temporary++);
            printf("%s = %s %c %s\n", temp, values[value_top - 2].value, postfix[i], values[value_top - 1].value);
            strcpy(values[value_top - 2].value, temp); value_top--;
        }
    }
    return 0;
}
