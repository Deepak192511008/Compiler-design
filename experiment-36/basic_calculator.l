%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
double result = 0, number;
char operation = '+';
int first = 1;
%}
%%
[0-9]+(\.[0-9]+)?  { number = atof(yytext); if (first) { result = number; first = 0; }
                       else if (operation == '+') result += number; else if (operation == '-') result -= number;
                       else if (operation == '*') result *= number; else if (operation == '/') result /= number; }
[+*/-]              { operation = yytext[0]; }
\n                  { printf("Result: %.2f\n", result); result = 0; first = 1; operation = '+'; }
[ \t]+              ;
.                   { printf("Invalid character: %s\n", yytext); }
%%
int main(void) { yylex(); return 0; }
