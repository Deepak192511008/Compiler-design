%option noyywrap
%{
#include <stdio.h>
int positive = 0, negative = 0;
%}
%%
-[0-9]+       { printf("NEGATIVE: %s\n", yytext); negative++; }
\+?[0-9]+     { printf("POSITIVE: %s\n", yytext); positive++; }
.              ;
%%
int main(void)
{
    yylex(); printf("Positive numbers: %d\nNegative numbers: %d\n", positive, negative); return 0;
}
