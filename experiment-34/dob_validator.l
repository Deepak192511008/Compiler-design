%option noyywrap
%{
#include <stdio.h>
%}
%%
([0-2][0-9]|3[01])/(0[1-9]|1[0-2])/[0-9]{4}  { printf("VALID DOB: %s\n", yytext); }
[^\n]+                                           { printf("INVALID DOB: %s\n", yytext); }
\n                                               ;
%%
int main(void) { yylex(); return 0; }
