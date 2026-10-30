%option noyywrap
%{
#include <stdio.h>
%}
%%
abc       fputs("ABC", yyout);
.|\n      ECHO;
%%
int main(void) { yyout = stdout; yylex(); return 0; }
