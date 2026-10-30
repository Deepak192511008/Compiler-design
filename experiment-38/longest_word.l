%option noyywrap
%{
#include <stdio.h>
#include <string.h>
char longest[256] = "";
%}
%%
[A-Za-z]+ { if (yyleng > (int)strlen(longest)) strcpy(longest, yytext); }
.|\n      ;
%%
int main(void) { yylex(); printf("Longest word: %s\nLength: %zu\n", longest, strlen(longest)); return 0; }
