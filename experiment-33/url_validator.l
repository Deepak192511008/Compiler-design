%option noyywrap
%{
#include <stdio.h>
%}
%%
https?://[A-Za-z0-9.-]+(/[A-Za-z0-9._/?=&%-]+)?  { printf("VALID URL: %s\n", yytext); }
[^\n]+                                               { printf("INVALID URL: %s\n", yytext); }
\n                                                   ;
%%
int main(void) { yylex(); return 0; }
