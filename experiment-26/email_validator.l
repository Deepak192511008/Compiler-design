%option noyywrap
%{
#include <stdio.h>
%}
%%
[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}  { printf("VALID EMAIL: %s\n", yytext); }
[^\n]+                                            { printf("INVALID EMAIL: %s\n", yytext); }
\n                                                ;
%%
int main(void) { yylex(); return 0; }
