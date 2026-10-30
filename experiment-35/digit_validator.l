%option noyywrap
%{
#include <stdio.h>
%}
%%
^[0-9]$       { printf("VALID DIGIT: %s\n", yytext); }
^[^\n]$       { printf("NOT A DIGIT: %s\n", yytext); }
\n            ;
%%
int main(void) { yylex(); return 0; }
