%option noyywrap
%{
#include <stdio.h>
%}
%%
^[6-9][0-9]{9}$   { printf("VALID MOBILE: %s\n", yytext); }
^[^\n]+$          { printf("INVALID MOBILE: %s\n", yytext); }
\n                ;
%%
int main(void) { yylex(); return 0; }
